/* 
 * File:   boundingBox.cpp
 * Author: miles
 * 
 * Created on June 6, 2014, 6:57 PM
 */

#include <utility>

#include "boundingBox.h"

boundingBox::boundingBox(const boundingBox& bb) :
    topFrontLeft{bb.topFrontLeft},
    botRearRight{bb.botRearRight}
{}

boundingBox::boundingBox(boundingBox&& bb) :
    topFrontLeft{std::move(bb.topFrontLeft)},
    botRearRight{std::move(bb.botRearRight)}
{
    bb.setTopFrontLeft(math::vec3{HL_EPSILON, HL_EPSILON, -HL_EPSILON});
    bb.setBotRearRight(math::vec3{-HL_EPSILON, -HL_EPSILON, HL_EPSILON});
}

boundingBox& boundingBox::operator=(const boundingBox& bb) {
    topFrontLeft = bb.topFrontLeft;
    botRearRight = bb.botRearRight;
    
    return *this;
}

boundingBox& boundingBox::operator =(boundingBox&& bb) {
    topFrontLeft = std::move(bb.topFrontLeft);
    botRearRight = std::move(bb.botRearRight);
    
    bb.setTopFrontLeft(math::vec3{HL_EPSILON, HL_EPSILON, -HL_EPSILON});
    bb.setBotRearRight(math::vec3{-HL_EPSILON, -HL_EPSILON, HL_EPSILON});
    
    return *this;
}

bool boundingBox::isInBox(const math::vec3& v) const {
    return
    v[0] <= topFrontLeft[0] && v[1] <= topFrontLeft[1] && v[2] >= topFrontLeft[2]
    &&
    v[0] >= botRearRight[0] && v[1] >= botRearRight[1] && v[2] <= botRearRight[2];
}

