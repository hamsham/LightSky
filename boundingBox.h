/* 
 * File:   boundingBox.h
 * Author: miles
 *
 * Created on June 6, 2014, 6:57 PM
 */

#ifndef __LS_BOUNDINGBOX_H__
#define	__LS_BOUNDINGBOX_H__

#include "main.h"

/**
 * Bounding Box Class
 * 
 * The orientation for a bounding box follows OpenGL coordinates, where the
 * positive XYZ coordinates point towards the top, right, front of the viewport.
 */
class boundingBox {
    private:
        math::vec3 topRearRight = {HL_EPSILON, HL_EPSILON, HL_EPSILON};
        math::vec3 botFrontLeft = {-HL_EPSILON, -HL_EPSILON, -HL_EPSILON};
        
    public:
        constexpr boundingBox() {}
        boundingBox(const boundingBox&);
        boundingBox(boundingBox&&);
        
        ~boundingBox() = default;
        
        boundingBox& operator=(const boundingBox&);
        boundingBox& operator=(boundingBox&&);
        
        bool isInBox(const math::vec3&) const;
        bool isColliding(const boundingBox&) const;
        
        void setTopRearRight(const math::vec3&);
        const math::vec3& getTopRearRight() const;
        
        void setBotFrontLeft(const math::vec3&);
        const math::vec3& getBotFrontLeft() const;
        
        void resetSize();
        
        /**
         * Compare a point to the current set of vertices.
         * If any of the components within the parameter are larger than the
         * components of this box, the current set of points will be enlarged.
         * 
         * @param point
         * A point who's individual components should be used to update the
         * size of this bounding box.
         */
        void compareAndUpdate(const math::vec3& point);
};
inline bool boundingBox::isColliding(const boundingBox& bb) const {
    return isInBox(bb.topRearRight) || isInBox(bb.botFrontLeft);
}

inline void boundingBox::setTopRearRight(const math::vec3& v) {
    topRearRight = v;
}

inline const math::vec3& boundingBox::getTopRearRight() const {
    return topRearRight;
}

inline void boundingBox::setBotFrontLeft(const math::vec3& v) {
    botFrontLeft = v;
}

inline const math::vec3& boundingBox::getBotFrontLeft() const {
    return botFrontLeft;
}

inline void boundingBox::resetSize() {
    setTopRearRight(math::vec3{HL_EPSILON, HL_EPSILON, HL_EPSILON});
    setBotFrontLeft(math::vec3{-HL_EPSILON, -HL_EPSILON, -HL_EPSILON});
}

#endif	/* __LS_BOUNDINGBOX_H__ */

