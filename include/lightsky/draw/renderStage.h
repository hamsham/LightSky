/* 
 * File:   renderStage.h
 * Author: Miles Lacey
 *
 * Created on January 20, 2015, 8:57 PM
 */

#ifndef __LS_DRAW_RENDER_STAGE_H__
#define	__LS_DRAW_RENDER_STAGE_H__

//#include <stack>

#include "lightsky/draw/setup.h"
#include "lightsky/draw/camera.h"
#include "lightsky/draw/sceneGraph.h"
#include "lightsky/draw/sceneNode.h"
#include "lightsky/draw/sceneMesh.h"
#include "lightsky/draw/shaderObject.h"
#include "lightsky/draw/shaderProgram.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * @brief The renderStage class is an abstract base class, describing the
 * basic functionality of a scene graph renderer. Use this interface to plan
 * out a renderer.
-----------------------------------------------------------------------------*/
class renderStage {
    private:
        /**
         * @brief The renderStackInfo struct is used specifically during draw
         * operations in order to ensure scene geometry is properly transformed
         * when drawn to a framebuffer.
         */
        /*
        struct renderStackInfo {
                sceneNode* pNode;
                unsigned childIter;
                math::mat4 modelMatrix;
        };
        */

        /**
         * @brief renderStack is an STL stack which maintains each scene node's
         * heirarchy of parent->child transformations. It was made a class
         * member rather than function variable due to the fact that STL
         * containers keep their maximum size if reallocated.
         */
        //std::stack<renderStackInfo> renderStack;

        /**
         * @brief Vertex shader which permits meshes to be manipulated before
         * being passed to the fragment shader.
         */
        vertexShader vertShader = {};

        /**
         * @brief Fragment shader which renders all transformed vertices and
         * geometry data to the currently bound framebuffer.
         */
        fragmentShader fragShader = {};

        /**
         * @brief The shader binary contains the linked vertex and fragment
         * shaders.
         */
        shaderProgram shaderBinary = {};

    protected:
        /**
         * @brief Retrieve the vertex shader contained within *this.
         * 
         * @return A reference to the vertex shader object used by *this.
         */
        vertexShader& getVertexShader();
        
        /**
         * @brief Retrieve the vertex shader contained within *this.
         * 
         * @return A const reference to the vertex shader object used by *this.
         */
        const vertexShader& getVertexShader() const;
        
        /**
         * @brief Retrieve the fragment shader contained within *this.
         * 
         * @return A reference to the fragment shader object used by *this.
         */
        fragmentShader& getFragmentShader();
        
        /**
         * @brief Retrieve the fragment shader contained within *this.
         * 
         * @return A constant reference to the fragment shader object used by
         * *this.
         */
        const fragmentShader& getFragmentShader() const;
        
        /**
         * @brief Retrieve the shader program object contained within *this.
         * 
         * @return A reference to the shader program used by *this.
         */
        shaderProgram& getShaderProgram();
        
        /**
         * @brief Retrieve the shader program object contained within *this.
         * 
         * @return A constant reference to the shader program used by *this.
         */
        const shaderProgram& getShaderProgram() const;
        
        /**
         * @brief Compile the vertex, fragment, and binary shader data in
         * *this.
         * 
         * Use this method (along with "linkShaders()" if the shader data
         * contained in *this requires framebuffer or transform feedback
         * attachments to be added to the pixel or vertex shader.
         * 
         * @param vertShaderData
         * A constant pointer to a constant c-style string, containing the
         * source data for a vertex shader.
         * 
         * @param fragShaderData
         * A constant pointer to a constant c-style string, containing the
         * source data for a vertex shader.
         * 
         * @return TRUE if the internal shader objects successfully compiled,
         * FALSE if not.
         */
        bool compileShaders(const char* const vertShaderData, const char* const fragShaderData);
        
        /**
         * @brief Link all shader data together in order to form a final
         * program binary on the GPU.
         * 
         * This function must be called if "compileShaders(...)" is used rather
         * than "initShaders(...)".
         * 
         * @return TRUE if all shader stages successfully linked together,
         * FALSE if not.
         */
        bool linkShaders();
        
        /**
         * @brief Compile and link all shader data in one single function,
         * rather than calling "compileShaders(...)" and "linkShaders()"
         * together.
         * 
         * @param vertShaderData
         * A constant pointer to a constant c-style string, containing the
         * source data for a vertex shader.
         * 
         * @param fragShaderData
         * A constant pointer to a constant c-style string, containing the
         * source data for a vertex shader.
         * 
         * @return TRUE if the internal shader objects successfully compiled
         * and linked, FALSE if not.
         */
        bool initShaders(const char* const vertShaderData, const char* const fragShaderData);
        
        /**
         * @brief Terminate all shader data and resources.
         * 
         * Shader objects will clean themselves up upon *this object's
         * destruction, however, this method should be explicitly called in
         * a derived object's "terminate()" method.
         */
        void terminateShaders();
        
        /**
         * @brief Iterate through all nodes in a scene graph and render them
         * to the currently bound framebuffer.
         * 
         * @param scene
         * A constant reference to the current scene that contains renderable
         * scene nodes.
         * 
         * @param node
         * A constant reference to the scene node which contains scene meshes
         * that are to be rendered.
         */
        virtual void drawSceneNode(const sceneGraph& scene, const sceneNode& node);
        
        /**
         * @brief drawNodeMesh is an abstract method which allows scene
         * renderers to implement their own per-node render method.
         * 
         * @param node
         * A constant reference to the scene node containing both the spatial
         * transformations and scene meshes to be rendered.
         * 
         * @param mesh
         * A constant reference to the scene mesh that is being rendered.
         */
        virtual void drawNodeMesh(const sceneNode& node, const sceneMesh& mesh);

    public:
        /**
         * @brief Destructor
         */
        virtual ~renderStage() = 0;

        /**
         * @brief Constructor
         * 
         * Initializes all members to their default values.
         */
        renderStage();

        /**
         * @brief Copy Constructor
         * 
         * Temporarily deleted.
         * 
         * @param rs
         * A constant reference to another renderStage object who's data will
         * be used to initialize *this.
         */
        renderStage(const renderStage& rs) = delete;

        /**
         * @brief Move Constructor
         * 
         * Move all members from the input parameter into *this without
         * performing any copies or re-initializations.
         * 
         * @param rs
         * An r-value reference to another renderStage object.
         */
        renderStage(renderStage&& rs);

        /**
         * @brief Copy Operator
         * 
         * Temporarily deleted.
         * 
         * @param rs
         * A constant reference to another renderStage object who's data will
         * be used to initialize *this.
         * 
         * @return A reference to *this.
         */
        renderStage& operator=(const renderStage& rs) = delete;

        /**
         * @brief Move Operator
         * 
         * Move all members from the input parameter into *this without
         * performing any copies or re-initializations.
         * 
         * @param rs
         * An r-value reference to another renderStage object.
         * 
         * @return A reference to *this.
         */
        renderStage& operator=(renderStage&& rs);

        /**
         * @brief init
         *
         * This method should be used to initialize the renderer for a scene
         * graph.
         *
         * @return TRUE if the scene graph renderer was successfully
         * initialized, or false if not.
         */
        virtual bool init() = 0;

        /**
         * @brief Terminate and free all resources used in a scene graph
         * renderer.
         */
        virtual void terminate() = 0;

        /**
         * @brief Bind *this object's shader program (and possibly other
         * rendering parameters) in preparation to render a scene.
         * 
         * This method must be called in order to render a scene graph to the
         * currently bound framebuffer.
         */
        virtual void bind();

        /**
         * @brief Unbind *this object's rendering parameters in order to allow
         * other OpenGL operations to be used without interference.
         */
        virtual void unbind();

        /**
         * @brief Render the data contained within a scene graph.
         *
         * This method traverses a scene graph and calls "drawSceneNode(...)"
         * for derived renderers to customize their rendering.
         *
         * @param scene
         * A constant reference to a constant sceneGraph.
         */
        virtual void draw(const sceneGraph& scene);

        /**
         * @brief Render the data contained within a scene graph.
         *
         * This method traverses a scene graph and calls "drawSceneNode(...)"
         * for derived renderers to customize their rendering.
         *
         * @param scene
         * A constant reference to a constant sceneGraph.
         * 
         * @param vpMatrix
         * The view/projection matrix from which all scene data will be viewed.
         */
        virtual void draw(const sceneGraph& scene, const math::mat4& vpMatrix);

        /**
         * @brief Render the data contained within a scene graph. Use a set of
         * node indices to draw specific nodes.
         *
         * This method traverses a scene graph and calls "drawSceneNode(...)"
         * for derived renderers to customize their rendering.
         *
         * @param scene
         * A constant reference to a constant sceneGraph.
         * 
         * @param vpMatrix
         * The view/projection matrix from which all scene data will be viewed.
         * 
         * @param nodeIndices
         * A std::vector of unsigned integers, specifying which nodes in the
         * sceneGraph object's array of nodes that should be rendered.
         */
        virtual void draw(
            const sceneGraph& scene,
            const math::mat4& vpMatrix,
            const std::vector<unsigned>& nodeIndices
        );
};

} // end draw namepsace
} // end ls namespace

#include "lightsky/draw/generic/renderStage_impl.h"

#endif	/* __LS_DRAW_RENDER_STAGE_H__ */

