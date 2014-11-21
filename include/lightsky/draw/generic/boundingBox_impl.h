
namespace ls {
namespace draw {

/*-------------------------------------
    Check if a point is within this box.
-------------------------------------*/
inline bool boundingBox::isInBox(const boundingBox& bb) const {
    return isInBox(bb.topRearRight) || isInBox(bb.botFrontLeft);
}

/*-------------------------------------
    Set the top-rear-right point of this bounding box.
-------------------------------------*/
inline void boundingBox::setTopRearRight(const math::vec3& v) {
    topRearRight = v;
}

/*-------------------------------------
    Get the top-rear-right point of this bounding box.
-------------------------------------*/
inline const math::vec3& boundingBox::getTopRearRight() const {
    return topRearRight;
}

/*-------------------------------------
    Set the bottom, front, left point of this bounding box.
-------------------------------------*/
inline void boundingBox::setBotFrontLeft(const math::vec3& v) {
    botFrontLeft = v;
}

/*-------------------------------------
    Get the bottom, front, left point of this bounding box.
-------------------------------------*/
inline const math::vec3& boundingBox::getBotFrontLeft() const {
    return botFrontLeft;
}

} // end draw namespace
} // end ls namespace
