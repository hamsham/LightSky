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

    protected:
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
         * @brief Bind a renderer to the current OpenGL context.
         */
        virtual void bind() = 0;

        /**
         * @brief Remove all renderer bindings from the active OpenGL
         * context.
         */
        virtual void unbind() = 0;

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

