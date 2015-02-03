/* 
 * File:   defaultRenderStage_impl.h
 * Author: hammy
 *
 * Created on February 2, 2015, 11:04 PM
 */

namespace ls {
namespace draw {
    
/*-------------------------------------
 * Draw a scene
-------------------------------------*/
inline void defaultRenderStage::draw(const sceneGraph& scene) {
    draw(scene, scene.getMainCamera().getVPMatrix());
}

} // end draw namespace
} // end ls namespace
