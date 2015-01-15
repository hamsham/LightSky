/* 
 * File:   draw/meshModel.cpp
 * Author: Miles Lacey
 * 
 * Created on June 10, 2014, 10:07 PM
 */

#include <utility>

#include "lightsky/utils/assertions.h"

#include "lightsky/draw/color.h"
#include "lightsky/draw/sceneNode.h"
#include "lightsky/draw/vertex.h"

namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
sceneNode::sceneNode() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
sceneNode::sceneNode(sceneNode&& s) :
    pMesh{s.pMesh}
{
    s.pMesh = nullptr;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
sceneNode::~sceneNode() {
}

sceneNode& sceneNode::operator=(sceneNode&& s) {
    pMesh = s.pMesh;
    s.pMesh = nullptr;
    
    return *this;
}

} // end draw namespace
} // end ls namespace
