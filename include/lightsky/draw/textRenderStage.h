/* 
 * File:   textRenderStage.h
 * Author: Miles Lacey
 *
 * Created on January 31, 2015, 4:52 PM
 */

#ifndef __LS_DRAW_TEXT_RENDER_STAGE_H__
#define	__LS_DRAW_TEXT_RENDER_STAGE_H__

#include "lightsky/draw/blendObject.h"
#include "lightsky/draw/camera.h"
#include "lightsky/draw/color.h"
#include "lightsky/draw/renderStage.h"
#include "lightsky/draw/shaderObject.h"
#include "lightsky/draw/shaderProgram.h"

namespace ls {
namespace draw {

/**
 * @brief The text render stage allows text geometry to be rendered through a
 * special shader which renders geometry with an alpha mask for clean, crisp
 * text.
 */
class textRenderStage : public renderStage {
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

        /**
         * @brief Shader uniform to set the current text color.
         */
        mutable int colorUniformId = -1;

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
        
        /**
         * @brief Color of the text to be rendered.
         */
        color::color textColor = color::black;
        
        /**
         * @brief Blend object used to keep text rendering pretty.
         */
        blendObject blender = {};

    public:
        /**
         * @brief Destructor
         * 
         * Calls "terminate()" if there are resources in *this which need to be
         * released.
         */
        virtual ~textRenderStage();

        /**
         * @brief Constructor
         * 
         * Initializes all members to their default values.
         */
        textRenderStage();

        /**
         * @brief Copy Constructor
         * 
         * Temporarily deleted.
         * 
         * @param rs
         * A constant reference to another textRenderStage object who's data
         * will be used to initialize *this.
         */
        textRenderStage(const textRenderStage& rs) = delete;

        /**
         * @brief Move Constructor
         * 
         * Move all members from the input parameter into *this without
         * performing any copies or re-initializations.
         * 
         * @param rs
         * An r-value reference to another textRenderStage object.
         */
        textRenderStage(textRenderStage&& rs);

        /**
         * @brief Copy Operator
         * 
         * Temporarily deleted.
         * 
         * @param rs
         * A constant reference to another textRenderStage object who's data
         * will be used to initialize *this.
         * 
         * @return A reference to *this.
         */
        textRenderStage& operator=(const textRenderStage& rs) = delete;

        /**
         * @brief Move Operator
         * 
         * Move all members from the input parameter into *this without
         * performing any copies or re-initializations.
         * 
         * @param rs
         * An r-value reference to another textRenderStage object.
         * 
         * @return A reference to *this.
         */
        textRenderStage& operator=(textRenderStage&& rs);

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
         * @brief Bind *this in preparation to render a scene.
         * 
         * This method must be called in order to render a scene graph to the
         * currently bound framebuffer.
         */
        virtual void bind() override;

        /**
         * @brief Unbind *this in order to allow other OpenGL operations to be
         * used without interference.
         */
        virtual void unbind() override;

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
         * The view/projection matrix which will be used to project rendered
         * vertices in the vertex shader.
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
         * The view/projection matrix which will be used to project rendered
         * vertices in the vertex shader.
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
        
        /**
         * @brief Set the color of the text to be rendered.
         * 
         * @param col
         * A color which will be applied to the rendered text
         * after it has been masked by an alpha texture containing font glyphs.
         */
        void setTextColor(const color::color& col);
        
        /**
         * @brief Get the color of the text to be rendered.
         * 
         * @return A constant reference to a color object which will be applied
         * to the rendered text after it has been masked by an alpha texture
         * containing font glyphs.
         */
        const color::color& getTextColor() const;
        
        /**
         * @brief Get the color of the text to be rendered.
         * 
         * @return A color object which will be applied to the rendered text
         * after it has been masked by an alpha texture containing font glyphs.
         */
        color::color& getTextColor();
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/textRenderStage_impl.h"

#endif	/* __LS_DRAW_TEXT_RENDER_STAGE_H__ */
