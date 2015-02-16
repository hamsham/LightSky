
#ifndef __LS_DRAW_PICKING_RENDER_STAGE_H__
#define __LS_DRAW_PICKING_RENDER_STAGE_H__

#include "lightsky/draw/pickingBuffer.h"
#include "lightsky/draw/renderStage.h"
#include "lightsky/draw/shaderObject.h"
#include "lightsky/draw/shaderProgram.h"

namespace ls {
namespace draw {

class pickingRenderStage final : virtual public renderStage {
    private:
        /**
         * @brief allow for custom vp matrices in the shaders
         */
        mutable int vpMatUniformId = 0;

        /**
         * @brief allow for custom model matrices in the shaders
         */
        mutable int modelMatUniformId = 0;

        /**
         * @brief get the index of all meshes being drawn
         */
        mutable int meshInstanceId = 0;

        /**
         * @brief Index of the node that should be highlighted
         */
        unsigned selectedNode = 0;

        /**
         * @brief Counting variable to help select the currently drawn scene
         * node.
         */
        unsigned currentNode = 0;

        /**
         * @brief Location of the currently selected pixel. A value of {-1, -1}
         * indicates that no pixel is selected.
         */
        math::vec2i pixelSelection = {-1, -1};

        /**
         * @brief Information about the current OpenGL Viewport size.
         */
        math::vec4i windowSize = {0, 0, 1, 1};

        /**
         * @brief Picking buffer object.
         */
        pickingBuffer selectionFbo;

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
        virtual void drawSceneNode(const sceneGraph& scene, const sceneNode& node) override;

    public:
        /**
         * @brief Destructor
         */
        virtual ~pickingRenderStage();

        /**
         * @brief Constructor
         */
        pickingRenderStage();

        /**
         * @brief Copy Constructor - DELETED
         */
        pickingRenderStage(const pickingRenderStage& rs) = delete;

        /**
         * @brief Move Constructor
         *
         * @param rs
         * An r-value reference to another picking render stage.
         */
        pickingRenderStage(pickingRenderStage&& rs);

        /**
         * @brief Copy Operator -- DELETED
         */
        pickingRenderStage& operator=(const pickingRenderStage& rs) = delete;

        /**
         * @brief Move Operator
         *
         * @param rs
         * An r-value to another render stage whis data will be moved into
         * *this.
         *
         * @return A reference to *this.
         */
        pickingRenderStage& operator=(pickingRenderStage&& rs);

        /**
         * @brief Picking Renderer initialization.
         *
         * @return TRUE if the data in *this was successfully initialized, false
         * if not.
         */
        virtual bool init() override;

        /**
         * @brief Resource termination
         */
        virtual void terminate() override;

        /**
         * @brief Activate the renderer and prepare it for use within the
         * current OpenGL context.
         */
        virtual void bind() override;

        /**
         * @brief Release the renderer from the current OpenGL context.
         */
        virtual void unbind() override;

        /**
         * @brief Render a scene graph into the picking buffer contained within
         * *this.
         *
         * @param scene
         * A constant reference to a scene graph object to be rendered.
         */
        virtual void draw(const sceneGraph& scene) override;

        /**
         * @brief Render a scene graph into the picking buffer contained within
         * *this, using a view-projection matrix other than the one provided
         * by the scene graph's camera.
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

        /**
         * @brief Determine if a scene node was selected from a pixel during
         * the last draw operation.
         *
         * @return The index of the scene node within a scene graph that was
         * selected through a pixel on the screen.
         */
        unsigned getSelectedNode() const;

        /**
         * @brief Get a reference to the selection buffer used by *this.
         *
         * @return A constant reference to the selection bufffer used by *this.
         */
        const pickingBuffer& getPickingBuffer() const;

        /**
         * @brief Get a reference to the selection buffer used by *this.
         *
         * @return A reference to the selection buffer.
         */
        pickingBuffer& getPickingBuffer();

        /**
         * @brief Determine which pixel is used by *this to pick a scene node
         * from the selection buffer.
         *
         * @return The x/y coordinate of a pixel used for object selection
         * within the selection buffer.
         */
        const math::vec2i& getCursorPosition() const;

        /**
         * @brief Set the x/y coordinate of the pixel that will be used to
         * identify scene nodes rendered to the screen.
         *
         * @param x
         * The X pixel coordinate.
         *
         * @param y
         * The Y-pixel coordinate.
         */
        void setCursorPosition(int x, int y);

        /**
         * @brief Set the x/y coordinate of the pixel that will be used to
         * identify scene nodes rendered to the screen.
         *
         * @param pos
         * A constant reference to a 2D integer vector, containing the x/y
         * coodinate of the pixel which will be used to select a scene node.
         */
        void setCursorPosition(const math::vec2i& pos);
};

} // end draw namespace
} // end ls namespace

#endif // __LS_DRAW_PICKING_RENDER_STAGE_H__

