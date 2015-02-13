/* 
 * File:   defaultRenderStage.h
 * Author: Miles Lacey
 *
 * Created on January 20, 2015, 9:29 PM
 */

#ifndef __LS_DRAW_DEFAULT_RENDER_STAGE_H__
#define __LS_DRAW_DEFAULT_RENDER_STAGE_H__

#include "lightsky/draw/renderStage.h"

namespace ls {
namespace draw {

/**------------------------------------
 * @brief The default render stage contains all OpenGL resources required to
 * render a scene after it has been imported from a sceneResource.
-------------------------------------*/
class defaultRenderStage final : public renderStage {
    private:
        /**
         * @brief Shader uniform to set the scene's camera in a shader.
         */
        mutable int vpMatUniformId = -1;

        /**
         * @brief Shader uniform to set a scene node's model matrix in a
         * shader.
         */
        mutable int modelMatUniformId = -1;

    public:
        /**
         * @brief Destructor
         * 
         * Calls "terminate()" if there are resources in *this which need to be
         * released.
         */
        virtual ~defaultRenderStage();

        /**
         * @brief Constructor
         * 
         * Initializes all members to their default values.
         */
        defaultRenderStage();

        /**
         * @brief Copy Constructor
         * 
         * Temporarily deleted.
         * 
         * @param rs
         * A constant reference to another defaultRenderStage object who's data
         * will be used to initialize *this.
         */
        defaultRenderStage(const defaultRenderStage& rs) = delete;

        /**
         * @brief Move Constructor
         * 
         * Move all members from the input parameter into *this without
         * performing any copies or re-initializations.
         * 
         * @param rs
         * An r-value reference to another defaultRenderStage object.
         */
        defaultRenderStage(defaultRenderStage&& rs);

        /**
         * @brief Copy Operator
         * 
         * Temporarily deleted.
         * 
         * @param rs
         * A constant reference to another defaultRenderStage object who's data
         * will be used to initialize *this.
         * 
         * @return A reference to *this.
         */
        defaultRenderStage& operator=(const defaultRenderStage& rs) = delete;

        /**
         * @brief Move Operator
         * 
         * Move all members from the input parameter into *this without
         * performing any copies or re-initializations.
         * 
         * @param rs
         * An r-value reference to another defaultRenderStage object.
         * 
         * @return A reference to *this.
         */
        defaultRenderStage& operator=(defaultRenderStage&& rs);

        /**
         * @brief Initialize all GPU-side resources in *this in order to
         * render scene data to the currently bound framebuffer.
         * 
         * @return TRUE if all data was successfully initialized, FALSE if not.
         */
        virtual bool init() override;

        /**
         * @brief Terminate *this by freeing all members and resources.
         */
        virtual void terminate() override;

        /**
         * @brief Render the data contained within a scene graph.
         *
         * This method traverses a scene graph and calls "drawSceneNode(...)"
         * for derived renderers to customize their rendering.
         *
         * @param scene
         * A constant reference to a constant sceneGraph.
         */
        virtual void draw(const sceneGraph& scene) override;

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
        virtual void draw(const sceneGraph& scene, const math::mat4& vpMatrix) override;

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
        ) override;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/defaultRenderStage_impl.h"

#endif /* __LS_DRAW_DEFAULT_RENDER_STAGE_H__ */

