/* 
 * File:   draw/sceneNode.h
 * Author: Miles Lacey
 *
 * Created on June 10, 2014, 10:07 PM
 */

#ifndef __LS_DRAW_SCENE_NODE_H__
#define	__LS_DRAW_SCENE_NODE_H__

#include <vector>
#include <deque>

#include "lightsky/draw/sceneMesh.h"
#include "lightsky/draw/transform.h"

namespace ls {
namespace draw {

struct sceneNode;

typedef std::deque<sceneNode> scene_node_list_t;

/**
 * A sceneNode represents a single renderable mesh that can be drawn multiple
 * times by attaching both an mesh and a set of model matrices. The more model
 * matrices that are bound to a mesh model, the more instances will be rendered
 * by OpenGL.
 */
struct sceneNode final {
    /**
     * @brief nodeParent is a pointer to the parent scene node.
     */
    sceneNode* nodeParent;

    /**
     * @brief nodeName
     *
     * A std::string object containing the name of this node in a scene.
     */
    std::string nodeName;

    /**
     * @brief nodeTransforms contains the position, orientation, and scale of
     * *this node's mesh instances in 3D Cartesian coordinates.
     */
    transform nodeTransform;
    
    /**
     * @brief nodeMeshes is the indices of the mesh that *this refers to in the
     * parent scene.
     */
    std::vector<sceneMesh*> nodeMeshes;

    /**
     * @brief nodeChildren is an array of sub-nodes whose transformations are
     * subject to the ones made by *this.
     */
    std::vector<sceneNode*> nodeChildren;

    /**
     * @brief Destructor
     * 
     * Frees All memory and resources used by *this.
     */
    ~sceneNode();

    /**
     * @brief Default Constructor
     */
    sceneNode();

    /**
     * @brief Copy Constructor
     * 
     * Copies all references from the input parameter into *this.
     * 
     * @param n
     * A constant reference to another node object.
     */
    sceneNode(const sceneNode& n);

    /**
     * @brief Move Constructor
     * 
     * Moves all data from the input parameter into *this. No copies are
     * performed.
     * 
     * @param n
     * An R-Value reference to a sceneNode that is about to go out of scope.
     */
    sceneNode(sceneNode&& n);

    /**
     * @brief Copy Operator
     * 
     * Copies all references from the input parameter into *this.
     * 
     * @param n
     * A constant reference to another node object.
     * 
     * @return A reference to *this.
     */
    sceneNode& operator=(const sceneNode& s);

    /**
     * @brief Move Operator
     * 
     * Moves all data from the input parameter into *this.
     * 
     * @param n
     * An R-Value reference to a sceneNode that is about to go out of scope.
     * 
     * @return A reference to *this.
     */
    sceneNode& operator=(sceneNode&& n);
    
    /**
     * @brief Reset all parameters to their default values.
     */
    void reset();
};

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_SCENE_NODE_H__ */
