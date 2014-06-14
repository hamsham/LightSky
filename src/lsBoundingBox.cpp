/* 
 * File:   boundingBox.cpp
 * Author: miles
 * 
 * Created on June 6, 2014, 6:57 PM
 */

#include <utility>

#include "lsBoundingBox.h"

lsBoundingBox::lsBoundingBox(const lsBoundingBox& bb) :
    topRearRight{bb.topRearRight},
    botFrontLeft{bb.botFrontLeft}
{}

lsBoundingBox::lsBoundingBox(lsBoundingBox&& bb) :
    topRearRight{std::move(bb.topRearRight)},
    botFrontLeft{std::move(bb.botFrontLeft)}
{
    bb.resetSize();
}

lsBoundingBox& lsBoundingBox::operator=(const lsBoundingBox& bb) {
    topRearRight = bb.topRearRight;
    botFrontLeft = bb.botFrontLeft;
    
    return *this;
}

lsBoundingBox& lsBoundingBox::operator =(lsBoundingBox&& bb) {
    topRearRight = std::move(bb.topRearRight);
    botFrontLeft = std::move(bb.botFrontLeft);
    
    bb.resetSize();
    
    return *this;
}

bool lsBoundingBox::isInBox(const math::vec3& v) const {
    return
    v[0] <= topRearRight[0] && v[1] <= topRearRight[1] && v[2] <= topRearRight[2]
    &&
    v[0] >= botFrontLeft[0] && v[1] >= botFrontLeft[1] && v[2] >= botFrontLeft[2];
}

void lsBoundingBox::compareAndUpdate(const math::vec3& point) {
    math::vec3& trr = topRearRight;
    if (point[0] > trr[0]) {trr[0] = point[0];}
    if (point[1] > trr[1]) {trr[1] = point[1];}
    if (point[2] > trr[2]) {trr[2] = point[2];}
    
    math::vec3& bfl = botFrontLeft;
    if (point[0] < bfl[0]) {bfl[0] = point[0];}
    if (point[1] < bfl[1]) {bfl[1] = point[1];}
    if (point[2] < bfl[2]) {bfl[2] = point[2];}
}

void lsBoundingBox::resetSize() {
    setTopRearRight(math::vec3{HL_EPSILON, HL_EPSILON, HL_EPSILON});
    setBotFrontLeft(math::vec3{-HL_EPSILON, -HL_EPSILON, -HL_EPSILON});
}
