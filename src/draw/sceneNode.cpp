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
    Destructor
-------------------------------------*/
sceneNode::~sceneNode() {
}

/*-------------------------------------
    Constructor
-------------------------------------*/
sceneNode::sceneNode() :
    nodeMeshIndex{},
    nodeParent{nullptr},
    nodeName{"Empty"},
    nodeTransform{},
    nodeChildren{}
{}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
sceneNode::sceneNode(const sceneNode& s) :
    nodeMeshIndex{s.nodeMeshIndex},
    nodeParent{s.nodeParent},
    nodeName{s.nodeName},
    nodeTransform{s.nodeTransform},
    nodeChildren{s.nodeChildren}
{}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
sceneNode::sceneNode(sceneNode&& s) :
    nodeMeshIndex{std::move(s.nodeMeshIndex)},
    nodeParent{s.nodeParent},
    nodeName{std::move(s.nodeName)},
    nodeTransform{std::move(s.nodeTransform)},
    nodeChildren{std::move(s.nodeChildren)}
{
    s.nodeMeshIndex = 0; // root node
    s.nodeParent = nullptr;
}

/*-------------------------------------
    Copy Operator
-------------------------------------*/
sceneNode& sceneNode::operator=(const sceneNode& s) {
    nodeMeshIndex = s.nodeMeshIndex;
    nodeParent = s.nodeParent;
    nodeName = s.nodeName;
    nodeTransform = s.nodeTransform;
    nodeChildren = s.nodeChildren;
    
    return *this;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
sceneNode& sceneNode::operator=(sceneNode&& s) {
    nodeMeshIndex = s.nodeMeshIndex;
    s.nodeMeshIndex = 0;
    
    nodeParent = s.nodeParent;
    s.nodeParent = nullptr;
    
    nodeName = std::move(s.nodeName);
    nodeTransform = std::move(s.nodeTransform);
    nodeChildren = std::move(s.nodeChildren);
    
    return *this;
}

/*-------------------------------------
    Reset
-------------------------------------*/
void sceneNode::reset() {
    *this = std::move(sceneNode{});
}

} // end draw namespace
} // end ls namespace
