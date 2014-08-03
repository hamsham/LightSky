/* 
 * File:   lsBoundingBox.h
 * Author: miles
 *
 * Created on June 6, 2014, 6:57 PM
 */

#ifndef __LS_BOUNDING_BOX_H__
#define	__LS_BOUNDING_BOX_H__

#include "lsSetup.h"

/**
 * Bounding Box Class
 * 
 * The orientation for a bounding box follows OpenGL coordinates, where the
 * positive XYZ coordinates point towards the top, right, front of the viewport.
 */
class lsBoundingBox {
    private:
        math::vec3 topRearRight = {1.f, 1.f, 1.f};
        math::vec3 botFrontLeft = {-1.f, -1.f, -1.f};
        
    public:
        /**
         * Constructor
         * 
         * Defaulted
         */
        lsBoundingBox();
        
        /**
         * Copy Constructor
         * 
         * Copies data from another bounding box.
         * 
         * @param A constant reference to a fully constructed bounding box
         * object.
         */
        lsBoundingBox(const lsBoundingBox&);
        
        /**
         * Move Constructor
         * 
         * Copies data from another bounding box (no moves are performed).
         * 
         * @param An r-value reference to a fully constructed bounding box
         */
        lsBoundingBox(lsBoundingBox&&);
        
        /**
         * Destructor
         * 
         * Defaulted
         */
        ~lsBoundingBox() = default;
        
        /**
         * Copy Operator
         * 
         * Copies data from another bounding box.
         * 
         * @param A constant reference to a fully constructed bounding box
         * object.
         * 
         * @return A reference to *this.
         */
        lsBoundingBox& operator=(const lsBoundingBox&);
        
        /**
         * Move Operator
         * 
         * @param An R-Value reference to a bounding box that is about to go
         * out of scope.
         * 
         * @return A reference to *this.
         */
        lsBoundingBox& operator=(lsBoundingBox&&);
        
        /**
         * Check if a point is within this box.
         * 
         * @param A constant reference to a vec3 object.
         * 
         * @return TRUE if the point is within *this, or FALSE if otherwise.
         */
        bool isInBox(const math::vec3&) const;
        
        /**
         * Check if a portion of another bounding box is within *this.
         * 
         * @param A constant reference to another bounding box.
         * 
         * @return TRUE if a portion of the bounding box is within *this, or
         * FALSE if it isn't.
         */
        bool isInBox(const lsBoundingBox&) const;
        
        /**
         * Set the top-rear-right point of this bounding box.
         * 
         * @param A constant reference to a point that will be used as the top,
         * rear, right point of this bounding box.
         */
        void setTopRearRight(const math::vec3&);
        
        /**
         * Get the top-rear-right point of this bounding box.
         * 
         * @return A constant reference to the top, rear, right point of this
         * bounding box.
         */
        const math::vec3& getTopRearRight() const;
        
        /**
         * Set the bottom, front, left point of this bounding box.
         * 
         * @param A constant reference to a point that will be used as the
         * bottom, front, left point of this bounding box.
         */
        void setBotFrontLeft(const math::vec3&);
        
        /**
         * Get the bottom, front, left point of this bounding box.
         * 
         * @return A constant reference to the bottom, front, left point of this
         * bounding box.
         */
        const math::vec3& getBotFrontLeft() const;
        
        /**
         * Reset the bounds of this bounding box to their default values.
         */
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

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Check if a point is within this box.
 */
inline bool lsBoundingBox::isInBox(const lsBoundingBox& bb) const {
    return isInBox(bb.topRearRight) || isInBox(bb.botFrontLeft);
}

/*
 * Set the top-rear-right point of this bounding box.
 */
inline void lsBoundingBox::setTopRearRight(const math::vec3& v) {
    topRearRight = v;
}

/*
 * Get the top-rear-right point of this bounding box.
 */
inline const math::vec3& lsBoundingBox::getTopRearRight() const {
    return topRearRight;
}

/*
 * Set the bottom, front, left point of this bounding box.
 */
inline void lsBoundingBox::setBotFrontLeft(const math::vec3& v) {
    botFrontLeft = v;
}

/*
 * Get the bottom, front, left point of this bounding box.
 */
inline const math::vec3& lsBoundingBox::getBotFrontLeft() const {
    return botFrontLeft;
}

#endif	/* __LS_BOUNDING_BOX_H__ */

