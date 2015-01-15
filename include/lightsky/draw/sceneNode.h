/* 
 * File:   draw/sceneNode.h
 * Author: Miles Lacey
 *
 * Created on June 10, 2014, 10:07 PM
 */

#ifndef __LS_DRAW_SCENE_NODE_H__
#define	__LS_DRAW_SCENE_NODE_H__

#include <vector>

#include "lightsky/draw/sceneMesh.h"
#include "lightsky/draw/texture.h"

namespace ls {
namespace draw {

/**
 * A sceneNode represents a single renderable mesh that can be drawn multiple
 * times by attaching both an mesh and a set of model matrices. The more model
 * matrices that are bound to a mesh model, the more instances will be rendered
 * by OpenGL.
 */
class sceneNode final {
    private:
        /**
         * @brief geometryId contains the index value of the geometry being used
         * in the parent scene object's array of GPU vertex data.
         */
        unsigned geometryId;

        /**
         * @brief pParent is a pointer to the parent scene node.
         */
        sceneNode* pParent;
    
        /**
         * @brief pMesh points to the mesh that should be drawn using *this.
         */
        sceneMesh* pMesh = nullptr;
        
    public:
        /**
         * @brief Default Constructor
         */
        sceneNode();
        
        /**
         * @brief Copy Constructor -- DELETED
         */
        sceneNode(const sceneNode& n) = delete;
        
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
         * @brief Destructor
         * 
         * Frees All memory and resources used by *this.
         */
        ~sceneNode();
        
        /**
         * @brief Copy Operator -- DELETED
         */
        sceneNode& operator=(const sceneNode& s) = delete;
        
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
};

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_SCENE_NODE_H__ */
