/* 
 * File:   sceneGraph.h
 * Author: Miles Lacey
 *
 * Created on January 19, 2015, 10:08 PM
 */

#ifndef __LS_DRAW_SCENE_GRAPH_H__
#define	__LS_DRAW_SCENE_GRAPH_H__

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
        std::vector<camera*> cameraList;

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
        
        bool importGeometry(const sceneResource& r);
        bool importMeshes(const sceneResource& r);
        bool importNodes(const sceneResource& r, const unsigned meshOffset);

    public:
        /**
         * @brief Destructor
         *
         * Releases all memory used by *this by calling "terminate()"
         */
        ~sceneGraph();

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
         * @return TRUE if all data was successfully loaded into *this and
         * the GPU, FALSE if not.
         */
        bool init(const sceneResource& r);

        /**
         * @brief Release all memory and resources used by *this.
         *
         * This method will reset all parameters to their default values.
         */
        void terminate();

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
         * @brief Get a constant reference to the list of cameras in *this.
         *
         * @return A constant reference to the cameras used for rendering the
         * scene.
         */
        const std::vector<camera*>& getCameraList() const;

        /**
         * @brief Get a reference to the list of cameras in *this.
         *
         * @return A constant reference to the cameras used for rendering the
         * scene.
         */
        std::vector<camera*>& getCameraList();

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

/*-------------------------------------
 * Get the root node in *this (const).
-------------------------------------*/
inline const sceneNode& sceneGraph::getRootNode() const {
    return rootNode;
}

/*-------------------------------------
 * Get the root node in *this.
-------------------------------------*/
inline sceneNode& sceneGraph::getRootNode() {
    return rootNode;
}

/*-------------------------------------
 * Get the list of textures used in *this (const).
-------------------------------------*/
inline const std::vector<texture*>& sceneGraph::getTextureList() const {
    return textureList;
}

/*-------------------------------------
 * Get the list of textures used in *this
-------------------------------------*/
inline std::vector<texture*>& sceneGraph::getTextureList() {
    return textureList;
}

/*-------------------------------------
 * Get the list of geometry used in *this (const).
-------------------------------------*/
inline const std::vector<geometry*>& sceneGraph::getGeometryList() const {
    return geometryList;
}

/*-------------------------------------
 * Get the list of geometry used in *this
-------------------------------------*/
inline std::vector<geometry*>& sceneGraph::getGeometryList() {
    return geometryList;
}

/*-------------------------------------
 * Get the list of meshes used in *this (const).
-------------------------------------*/
inline const std::vector<sceneMesh*>& sceneGraph::getMeshList() const {
    return meshList;
}

/*-------------------------------------
 * Get the list of meshes used in *this
-------------------------------------*/
inline std::vector<sceneMesh*>& sceneGraph::getMeshList() {
    return meshList;
}

/*-------------------------------------
 * Get the list of nodes used in *this (const).
-------------------------------------*/
inline const scene_node_list_t& sceneGraph::getNodeList() const {
    return nodeList;
}

/*-------------------------------------
 * Get the list of nodes used in *this.
-------------------------------------*/
inline scene_node_list_t& sceneGraph::getNodeList() {
    return nodeList;
}

/*-------------------------------------
 * Get the camera transformation (const)
-------------------------------------*/
inline const std::vector<camera*>& sceneGraph::getCameraList() const {
    return cameraList;
}

/*-------------------------------------
 * Get the camera transformation
-------------------------------------*/
inline std::vector<camera*>& sceneGraph::getCameraList() {
    return cameraList;
}

} // end draw namepsace
} // end ls namespace

#endif	/* __LS_DRAW_SCENE_GRAPH_H__ */

