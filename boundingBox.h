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
        
        ~boundingBox() = default;
        
        boundingBox& operator=(const boundingBox&);
        boundingBox& operator=(boundingBox&&);
        
        bool isInBox(const math::vec3&) const;
        bool isColliding(const boundingBox&) const;
        
        void setTopFrontLeft(const math::vec3&);
        const math::vec3& getTopFrontLeft() const;
        
        void setBotRearRight(const math::vec3&);
        const math::vec3& getBotRearRight() const;
};
inline bool boundingBox::isColliding(const boundingBox& bb) const {
    return isInBox(bb.topFrontLeft) || isInBox(bb.botRearRight);
}

inline void boundingBox::setTopFrontLeft(const math::vec3& v) {
    topFrontLeft = v;
}

inline const math::vec3& boundingBox::getTopFrontLeft() const {
    return topFrontLeft;
}

inline void boundingBox::setBotRearRight(const math::vec3& v) {
    botRearRight = v;
}

inline const math::vec3& boundingBox::getBotRearRight() const {
    return botRearRight;
}

#endif	/* __LS_BOUNDINGBOX_H__ */

