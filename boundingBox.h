/* 
 * File:   boundingBox.h
 * Author: miles
 *
 * Created on June 6, 2014, 6:57 PM
 */

#ifndef __LS_BOUNDINGBOX_H__
#define	__LS_BOUNDINGBOX_H__

#include "main.h"

class boundingBox {
    private:
        math::vec3 topFrontLeft = {HL_EPSILON, HL_EPSILON, -HL_EPSILON};
        math::vec3 botRearRight = {-HL_EPSILON, -HL_EPSILON, HL_EPSILON};
        
    public:
        constexpr boundingBox() {}
        boundingBox(const boundingBox&);
        boundingBox(boundingBox&&);
        
        ~boundingBox() {}
        
        boundingBox& operator=(const boundingBox&);
        boundingBox& operator=(boundingBox&&);
        
        constexpr bool isInBox(const math::vec3&) const;
        constexpr bool isColliding(const boundingBox&) const;
        
        constexpr void setTopFrontLeft(const math::vec3&);
        constexpr math::vec3& getTopFrontLeft() const;
        
        constexpr void setBotRearRight(const math::vec3&);
        constexpr math::vec3& getBotRearRight() const;
};

constexpr bool boundingBox::isInBox(const math::vec3& v) const {
    return
    v[0] <= topFrontLeft[0] && v[1] <= topFrontLeft[1] && v[2] >= topFrontLeft[2]
    &&
    v[0] >= botRearRight[0] && v[1] >= botRearRight[1] && v[2] <= botRearRight[2];
}

constexpr bool boundingBox::isColliding(const boundingBox& bb) const {
    return isInBox(bb.topFrontLeft) || isInBox(bb.botRearRight);
}

constexpr void boundingBox::setTopFrontLeft(const math::vec3& v) {
    topFrontLeft = v;
}

constexpr math::vec3& boundingBox::getTopFrontLeft() const {
    return topFrontLeft;
}

constexpr void boundingBox::setBotRearRight(const math::vec3& v) {
    botRearRight = v;
}

constexpr math::vec3& boundingBox::getBotRearRight() const {
    return botRearRight;
}

#endif	/* __LS_BOUNDINGBOX_H__ */

