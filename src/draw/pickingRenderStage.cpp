
#include "lightsky/draw/setup.h"
#include "lightsky/draw/pickingRenderStage.h"
#include "lightsky/draw/sceneGraph.h"
#include "lightsky/draw/sceneNode.h"

/*-----------------------------------------------------------------------------
 * Private Shader data
-----------------------------------------------------------------------------*/
namespace {

/**------------------------------------
 * @brief UNIFORM_MAT4_VP
 *
 * OpenGL Shader uniform for the camera's combined view and
 * projection matrices.
-------------------------------------*/
const char* const UNIFORM_MAT4_VP = "vpMatrix";

/**------------------------------------
 * @brief UNIFORM_MAT4_MODEL
 *
 * OpenGL Shader uniform for a rendered object's model matrix.
-------------------------------------*/
const char* const UNIFORM_MAT4_MODEL = "modelMatrix";

/**------------------------------------
 * @brief UNIFORM_MESH_INSTANCE_ID
 *
 * Applies a shader-side ID to the current mesh being rendered.
-------------------------------------*/
const char* const UNIFORM_MESH_INSTANCE_ID = "meshId";

/**------------------------------------
 * @brief SHADER_FILE_VERT
 *
 * OpenGL Vertex Shader file location.
-------------------------------------*/
const char PICKING_SHADER_VERT_DATA[] = u8R"***(
attribute vec3 pos;

uniform mat4 vpMatrix;
uniform mat4 modelMatrix;

void main() {
    mat4 mvpMatrix = vpMatrix * modelMatrix;
    gl_Position = mvpMatrix * vec4(pos, 1.0);
}
)***";

/**------------------------------------
 * @brief SHADER_FILE_FRAG
 *
 * OpenGL Fragment Shader file location.
-------------------------------------*/
const char PICKING_SHADER_FRAG_DATA[] = u8R"***(
uniform vec4 meshId;

void main() {
    gl_FragColor = meshId;
}
)***";

} // end anonymous namespace

/*-----------------------------------------------------------------------------
 * Picking Render Stage Class
-----------------------------------------------------------------------------*/
namespace ls {
namespace draw {

/*-------------------------------------
 * Destructor
-------------------------------------*/
pickingRenderStage::~pickingRenderStage() {
    terminate();
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
pickingRenderStage::pickingRenderStage() :
    renderStage{},
    vpMatUniformId{0},
    modelMatUniformId{0},
    meshInstanceId{0},
    selectedNode{0},
    currentNode{0},
    pixelSelection{-1, -1},
    windowSize{0, 0, 1, 1},
    selectionFbo{}
{}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
pickingRenderStage::pickingRenderStage(pickingRenderStage&& rs) :
    renderStage{std::move(rs)},
    vpMatUniformId{rs.vpMatUniformId},
    modelMatUniformId{rs.modelMatUniformId},
    meshInstanceId{rs.meshInstanceId},
    selectedNode{rs.selectedNode},
    currentNode{0},
    pixelSelection{std::move(rs.pixelSelection)},
    windowSize{std::move(rs.windowSize)},
    selectionFbo{std::move(rs.selectionFbo)}
{
    rs.vpMatUniformId = 0;
    rs.modelMatUniformId = 0;
    rs.meshInstanceId = 0;
    rs.selectedNode = 0;
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
pickingRenderStage& pickingRenderStage::operator=(pickingRenderStage&& rs) {
    renderStage::operator=(std::move(rs));
    
    vpMatUniformId = rs.vpMatUniformId;
    rs.vpMatUniformId = 0;

    modelMatUniformId = rs.modelMatUniformId;
    rs.modelMatUniformId = 0;

    meshInstanceId = rs.meshInstanceId;
    rs.meshInstanceId = 0;

    selectedNode = rs.selectedNode;
    rs.selectedNode = 0;

    pixelSelection = std::move(rs.pixelSelection);

    windowSize = std::move(rs.windowSize);

    selectionFbo = std::move(rs.selectionFbo);

    return *this;
}

/*-------------------------------------
 * Initialization
-------------------------------------*/
bool pickingRenderStage::init() {
    LOG_GL_ERR();

    // add the mesh vertex & fragment shaders
    if (!initShaders(PICKING_SHADER_VERT_DATA, PICKING_SHADER_FRAG_DATA)) {
        LS_LOG_ERR("Failed to compile the shaders in a pickingRenderStage.");
        LOG_GL_ERR();
    }

    // attach the selection ID to the scene graph
    shaderProgram& shaderBinary = getShaderProgram();
    shaderBinary.bind();

    // shader uniform to select the current mesh
    meshInstanceId = shaderBinary.getUniformLocation(UNIFORM_MESH_INSTANCE_ID);
    if (meshInstanceId < 0) {
        LS_LOG_ERR("Unable to set the mesh scene's uniform variable \"meshInstanceId\".");
        LOG_GL_ERR();
    }

    // attach the model matrix uniform to the scene graph
    modelMatUniformId = shaderBinary.getUniformLocation(UNIFORM_MAT4_MODEL);
    if (modelMatUniformId < 0) {
        LS_LOG_ERR("Unable to set the mesh scene's uniform variable \"modelMatUniformId\".");
        LOG_GL_ERR();
    }

    // camera/view-projection uniform
    vpMatUniformId = shaderBinary.getUniformLocation(UNIFORM_MAT4_VP);
    if (vpMatUniformId < 0) {
        LS_LOG_ERR("Unable to set the mesh scene's uniform variable \"vpMatUniformId\".");
        LOG_GL_ERR();
    }

    LS_LOG_MSG("Successfully initialized all variables in the selection shader.");

    shaderBinary.unbind();

    LOG_GL_ERR();

    return true;
}

/*-------------------------------------
 * Resource Termination
-------------------------------------*/
void pickingRenderStage::terminate() {
    renderStage::terminate();
    
    vpMatUniformId = 0;
    modelMatUniformId = 0;
    meshInstanceId = 0;
    currentNode = 0;
    selectedNode = 0;

    pixelSelection = {-1, -1};
    windowSize = {0, 0, 1, 1};

    selectionFbo.terminate();
}

/*-------------------------------------
 * Renderer binding
-------------------------------------*/
void pickingRenderStage::bind() {
    renderStage::bind();

    math::vec4i windowResizeVal;

    // ensure that the current viewport is being used.
    glGetIntegerv(GL_VIEWPORT, windowResizeVal.v);

    // check if the selection buffer needs to be resized.
    if (windowResizeVal != windowSize) {
        if (!selectionFbo.init(windowResizeVal[2], windowResizeVal[3])) {
            LS_LOG_ERR("Unable to bind a picking render stage due to a bad framebuffer.");
            return;
        }
        windowSize = windowResizeVal;
    }

    selectionFbo.bind();
}

/*-------------------------------------
 * Unbind
-------------------------------------*/
void pickingRenderStage::unbind() {
    selectionFbo.unbind();
    renderStage::unbind();
}

/*-------------------------------------
 * Scene Graph Rendering
-------------------------------------*/
void pickingRenderStage::draw(const sceneGraph& scene, const math::mat4& vpMatrix) {
    const shaderProgram& shaderBinary = getShaderProgram();

    // ensure the viewport looks pretty
    shaderBinary.setUniformValue(vpMatUniformId, vpMatrix, false);
    
    currentNode = 0;
    
    renderStage::draw(scene, vpMatrix);

    const int x = pixelSelection[0];
    const int y = windowSize[3]-pixelSelection[1]; // openGL Special Y-coordinate
    selectedNode = selectionFbo.getIdAtLocation(x, y);
}

/*-------------------------------------
 * Scene Graph Rendering
-------------------------------------*/
void pickingRenderStage::draw(
    const sceneGraph& scene,
    const math::mat4& vpMatrix,
    const std::vector<unsigned>& nodeIndices
) {
    const shaderProgram& shaderBinary = getShaderProgram();

    // ensure the viewport looks pretty
    shaderBinary.setUniformValue(vpMatUniformId, vpMatrix, false);
    
    currentNode = 0;
    
    renderStage::draw(scene, vpMatrix, nodeIndices);

    const int x = pixelSelection[0];
    const int y = windowSize[3]-pixelSelection[1]; // openGL Special Y-coordinate
    selectedNode = selectionFbo.getIdAtLocation(x, y);
}

/*-------------------------------------
 * Render an individual scene node.
-------------------------------------*/
void pickingRenderStage::drawSceneNode(const sceneGraph&, const sceneNode& node) {
    LOG_GL_ERR();
    
    const shaderProgram& shaderBinary = getShaderProgram();

    // send the current node's index to a shader
    const color::colorf_t&& idColor = pickingBuffer::convertIdToPixelColor(currentNode++);
    shaderBinary.setUniformValue(meshInstanceId, idColor);

    const math::mat4& modelMatrix = node.nodeTransform.getTransform();
    shaderBinary.setUniformValue(modelMatUniformId, modelMatrix, false);

    for (const sceneMesh* pMesh : node.nodeMeshes) {
        pMesh->draw();
    }

    LOG_GL_ERR();
}

} // end draw namespace
} // end ls namespace

