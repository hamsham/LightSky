/* 
 * File:   sceneGraph.h
 * Author: Miles Lacey
 *
 * Created on January 19, 2015, 10:08 PM
 */

#ifndef __LS_DRAW_SCENE_GRAPH_H__
#define	__LS_DRAW_SCENE_GRAPH_H__

#include <stack>
#include <vector>

#include "lightsky/draw/sceneNode.h"

namespace ls {
namespace draw {

/*-----------------------------------------------------------------------------
 * Forward declarations
-----------------------------------------------------------------------------*/
class camera;
class geometry;
class texture;
class sceneMesh;
class sceneResource;

/**----------------------------------------------------------------------------
 * @brief The scene graph class manages a set of objects that can be
 * transformed and rendered to OpenGL.
 *
 * Renderable objects are placed into a heirarchy with parent/child
 * relationships. Parent nodes contain their own cartesian transformations which
 * are applied to their child nodes.
-----------------------------------------------------------------------------*/
class sceneGraph {
    private:
        /**
         * @brief The renderStackInfo struct is used specifically during draw
         * operations in order to ensure scene geometry is properly transformed
         * when drawn to a framebuffer.
         */
        struct nodeStackInfo {
            sceneNode* pNode;
            unsigned childIter;
            math::mat4 modelMatrix;
        };

        /**
         * @brief updateStack is an STL stack which maintains each scene node's
         * hierarchy of parent->child transformations. It was made a class
         * member rather than function variable due to the fact that STL
         * containers keep their maximum size if reallocated.
         */
        std::stack<nodeStackInfo> updateStack;
        
        /**
         * @brief rootNode
         *
         * The lead node from which all sub-node transformations are based.
         */
        sceneNode rootNode;

        /**
         * @brief cameraList
         *
         * Contains a list of view/projection transformations used to render
         * sceneNodes onto a framebuffer.
         */
        camera* pMainCamera;

        /**
         * @brief textureList
         *
         * Contains a list of all textures used by *this. Meshes will be
         * assigned an index to reference a single renderable geometry contained
         * within this array.
         */
        std::vector<texture*> textureList;

        /**
         * @brief geometryList
         *
         * Contains a list of all geometry used by *this. Meshes will be
         * assigned an index to reference a single renderable geometry contained
         * within this array.
         */
        std::vector<geometry*> geometryList;

        /**
         * @brief meshList
         *
         * Contains a list of all meshes used by *this. Meshes are used by nodes
         * for instanced rendering with textures.
         */
        std::vector<sceneMesh*> meshList;

        /**
         * @brief nodeList
         *
         * The list of all nodes that are drawn within the scene represented
         * by *this.
         */
        scene_node_list_t nodeList;
        
        /**
         * @brief Import a set of geometry into the scene graph.
         * 
         * @param r
         * A constant reference to a scene resource object, containing geometry
         * data which can be imported onto the GPU through *this.
         * 
         * @return TRUE if all geometry loaded onto the GPU correctly, FALSE if
         * something went wrong.
         */
        bool importGeometry(const sceneResource& r);
        
        /**
         * @brief Initialize all mesh objects from the scene resource object
         * into *this in order to draw geometry.
         * 
         * @param r
         * A constant reference to a scene resource object containing valid mesh
         * information.
         * 
         * @return TRUE if all mesh data loaded onto the GPU correctly, FALSE
         * if something went wrong.
         */
        bool importMeshes(const sceneResource& r);
        
        /**
         * @brief Import the scene's node hierarchy from a scene resource
         * object.
         * 
         * @param r
         * A constant reference to a scene resource object containing a valid
         * sceneNode hierarchy.
         * 
         * @param meshOffset
         * The index offset to the last mesh in *this object's mesh array. This
         * parameter will be greater than zero if the imported node hierarchy
         * is appended to the scene graph's previous data set.
         * 
         * @return TRUE if all scene nodes from the resource object loaded
         * successfully, FALSE if not.
         */
        bool importNodes(const sceneResource& r, const unsigned meshOffset);
    
    protected:
        /**
         * @brief Update the animations and transformations for a single node
         * in *this.
         * 
         * @param millisElapsed
         * The number of milliseconds which have passed since the last call to
         * "update()."
         * 
         * @param node
         * A reference to the scene node object which is to be updated.
         */
        void updateSceneNode(uint64_t millisElapsed, sceneNode& node);

    public:
        /**
         * @brief Destructor
         *
         * Releases all memory used by *this by calling "terminate()"
         */
        virtual ~sceneGraph();

        /**
         * @brief Constructor
         *
         * Initializes all data in *this to their default values.
         */
        sceneGraph();

        /**
         * @brief Copy Constructor -- DELETED
         */
        sceneGraph(const sceneGraph&) = delete;

        /**
         * @brief Move Constructor
         *
         * Moves all data from the input parameter into *this without
         * performing any copies.
         *
         * @param s
         * An r-value reference to another scene object.
         */
        sceneGraph(sceneGraph&& s);

        /**
         * @brief Copy Operator -- DELETED
         */
        sceneGraph& operator=(const sceneGraph&) = delete;

        /**
         * @brief Move Operator
         *
         * Moves all data from the input parameter into *this without
         * performing any copies.
         *
         * @param s
         * An r-value reference to another scene object.
         *
         * @return A reference to *this.
         */
        sceneGraph& operator=(sceneGraph&& s);

        /**
         * @brief Load all data from a sceneResource object into *this and
         * prepare it for rendering.
         *
         * Calling this method will move all data out of the sceneResource and
         * into *this, thereby invalidating the data contained within the
         * resource object.
         *
         * @param r
         * A constant reference to a sceneResource object containing renderable
         * scene data.
         * 
         * @param append
         * Set this parameter to TRUE if the imported scene resource object's
         * data should be added to *this. Set this parameter to FALSE if the
         * data in *this should be freed before importing.
         *
         * @return TRUE if all data was successfully loaded into *this and
         * the GPU, FALSE if not.
         */
        bool init(const sceneResource& r, bool append = false);

        /**
         * @brief Release all memory and resources used by *this.
         *
         * This method will reset all parameters to their default values.
         */
        void terminate();
        
        /**
         * @brief Update all animations and transformations in the scene.
         * 
         * @param millisElapsed
         * The number of milliseconds which have passed since the last call to
         * "update()."
         */
        void update(uint64_t millisElapsed);

        /**
         * @brief Retrieve the root node from which all scene data is based
         * on.
         *
         * @return A constant reference to a sceneNode object.
         */
        const sceneNode& getRootNode() const;

        /**
         * @brief Retrieve the root node from which all scene data is based
         * on.
         *
         * @return A reference to a sceneNode object.
         */
        sceneNode& getRootNode();

        /**
         * @brief Get a constant reference to primary camera in the scene.
         *
         * @return A constant reference to the main camera used for rendering.
         * If there is no camera in *this, a camera will be dynamically created.
         */
        const camera& getMainCamera() const;

        /**
         * @brief Get a reference to primary camera in the scene.
         *
         * @return A reference to the main camera used for rendering. If there
         * is no camera in *this, a camera will be dynamically created.
         */
        camera& getMainCamera();

        /**
         * @brief Get the array of textures used by *this scene object's
         * node graph.
         *
         * @return A constant reference to the array of textures used by
         * *this.
         */
        const std::vector<texture*>& getTextureList() const;

        /**
         * @brief Get the array of textures used by *this scene object's
         * node graph.
         *
         * @return A reference to the array of textures used by *this.
         */
        std::vector<texture*>& getTextureList();

        /**
         * @brief Get the array of geometry used by *this scene object's
         * node graph.
         *
         * @return A constant reference to the array of geometry used by
         * *this.
         */
        const std::vector<geometry*>& getGeometryList() const;

        /**
         * @brief Get the array of geometry used by *this scene object's
         * node graph.
         *
         * @return A reference to the array of geometry used by *this.
         */
        std::vector<geometry*>& getGeometryList();

        /**
         * @brief Get the array of scene meshes used by *this scene object's
         * node graph.
         *
         * @return A constant reference to the array of meshes used by *this.
         */
        const std::vector<sceneMesh*>& getMeshList() const;

        /**
         * @brief Get the array of scene meshes used by *this scene object's
         * node graph.
         *
         * @return A reference to the array of meshes used by *this.
         */
        std::vector<sceneMesh*>& getMeshList();

        /**
         * @brief Get the list of scene nodes which make up the scene graph.
         *
         * @return A constant reference to the list of scene nodes used by
         * *this.
         */
        const scene_node_list_t& getNodeList() const;

        /**
         * @brief Get the list of scene nodes which make up the scene graph.
         *
         * @return A reference to the list of scene nodes used by *this.
         */
        scene_node_list_t& getNodeList();
};

} // end draw namepsace
} // end ls namespace

#include "lightsky/draw/generic/sceneGraph_impl.h"

#endif	/* __LS_DRAW_SCENE_GRAPH_H__ */

