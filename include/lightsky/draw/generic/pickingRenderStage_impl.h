
namespace ls {
namespace draw {

/*-------------------------------------
 * Scene Gaph traversing for rendering.
-------------------------------------*/
inline void pickingRenderStage::draw(const sceneGraph& scene) {
    draw(scene, scene.getMainCamera().getVPMatrix());
}

/*-------------------------------------
 * Get the currently selected node.
-------------------------------------*/
inline unsigned pickingRenderStage::getSelectedNode() const {
    return selectedNode;
}

/*-------------------------------------
 * Get the selection buffer (const).
-------------------------------------*/
inline const pickingBuffer& pickingRenderStage::getPickingBuffer() const {
    return selectionFbo;
}

/*-------------------------------------
 * Get the selection buffer.
-------------------------------------*/
inline pickingBuffer& pickingRenderStage::getPickingBuffer() {
    return selectionFbo;
}

/*-------------------------------------
 * Get the current pixel cursor position.
-------------------------------------*/
inline const math::vec2i& pickingRenderStage::getCursorPosition() const {
    return pixelSelection;
}

/*-------------------------------------
 * Set the pixel cursor position
-------------------------------------*/
inline void pickingRenderStage::setCursorPosition(int x, int y) {
    pixelSelection[0] = x;
    pixelSelection[1] = y;
}

/*-------------------------------------
 * Set the pixel cursor position
-------------------------------------*/
inline void pickingRenderStage::setCursorPosition(const math::vec2i& pos) {
    pixelSelection = pos;
}

} // end draw namespace
} // end ls namespace
