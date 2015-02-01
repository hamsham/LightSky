/* 
 * File:   textRenderStage.cpp
 * Author: Miles Lacey
 * 
 * Created on January 31, 2015, 4:52 PM
 */

#include "lightsky/draw/textRenderStage.h"

namespace ls {
namespace draw {

textRenderStage::~textRenderStage() {
}

textRenderStage::textRenderStage() {
}

textRenderStage::textRenderStage(const textRenderStage&) {
}

textRenderStage::textRenderStage(textRenderStage&&) {
}

textRenderStage& textRenderStage::operator=(const textRenderStage&) {
    return *this;
}

textRenderStage& textRenderStage::operator=(textRenderStage&&) {
    return *this;
}

} // end draw namespace
} // end ls namespace
