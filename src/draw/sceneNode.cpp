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
    nodeParent{nullptr},
    nodeName{"Empty"},
    nodeTransform{},
    nodeMeshes{},
    nodeChildren{}
{}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
sceneNode::sceneNode(const sceneNode& s) :
    nodeParent{s.nodeParent},
    nodeName{s.nodeName},
    nodeTransform{s.nodeTransform},
    nodeMeshes{s.nodeMeshes},
    nodeChildren{s.nodeChildren}
{}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
sceneNode::sceneNode(sceneNode&& s) :
    nodeParent{s.nodeParent},
    nodeName{std::move(s.nodeName)},
    nodeTransform{std::move(s.nodeTransform)},
    nodeMeshes{std::move(s.nodeMeshes)},
    nodeChildren{std::move(s.nodeChildren)}
{
    s.nodeParent = nullptr;
}

/*-------------------------------------
    Copy Operator
-------------------------------------*/
sceneNode& sceneNode::operator=(const sceneNode& s) {
    nodeParent = s.nodeParent;
    nodeName = s.nodeName;
    nodeTransform = s.nodeTransform;
    nodeMeshes = s.nodeMeshes;
    nodeChildren = s.nodeChildren;
    
    return *this;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
sceneNode& sceneNode::operator=(sceneNode&& s) {
    nodeParent = s.nodeParent;
    s.nodeParent = nullptr;
    
    nodeName = std::move(s.nodeName);
    nodeTransform = std::move(s.nodeTransform);
    nodeMeshes = std::move(s.nodeMeshes);
    nodeChildren = std::move(s.nodeChildren);
    
    return *this;
}

/*-------------------------------------
    Reset
-------------------------------------*/
void sceneNode::reset() {
    nodeParent = nullptr;
    
    nodeName.clear();
    nodeTransform = transform{};
    nodeMeshes.clear();
    nodeChildren.clear();
}

} // end draw namespace
} // end ls namespace
