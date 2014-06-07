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
    bb = boundingBox{};
}

boundingBox& boundingBox::operator=(const boundingBox& bb) {
    topFrontLeft = bb.topFrontLeft;
    botRearRight = bb.botRearRight;
    
    return *this;
}

boundingBox& boundingBox::operator =(boundingBox&& bb) {
    topFrontLeft = std::move(bb.topFrontLeft);
    botRearRight = std::move(bb.botRearRight);
    
    bb = boundingBox{};
    
    return *this;
}
