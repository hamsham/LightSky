
namespace ls {
namespace draw {
    
/*-------------------------------------
 * Draw a scene
-------------------------------------*/
inline void textRenderStage::draw(const sceneGraph& scene) {
    draw(scene, scene.getMainCamera().getVPMatrix());
}

/*-------------------------------------
 * Set the current text color
-------------------------------------*/
inline void textRenderStage::setTextColor(const color::color& col) {
    textColor = col;
}

/*-------------------------------------
 * Get the current text color (const)
-------------------------------------*/
inline const color::color& textRenderStage::getTextColor() const {
    return textColor;
}

/*-------------------------------------
 * Get the current text color
-------------------------------------*/
inline color::color& textRenderStage::getTextColor() {
    return textColor;
}

} // end draw namespace
} // end ls namespace
