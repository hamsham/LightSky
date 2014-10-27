
namespace ls {
namespace draw {

/*-------------------------------------
 * Saving Data
-------------------------------------*/
inline bool imageResource::saveFile(const std::string& filename) const {
    return saveFile(filename, img_file_t::IMG_FILE_PNG);
}

/*-------------------------------------
 * Get the pixel size of the currently loaded image
-------------------------------------*/
inline math::vec2i imageResource::getPixelSize() const {
    return imgSize;
}

/*-------------------------------------
 * Get the GPU-compatible format of the currently loaded image
-------------------------------------*/
inline color_type_t imageResource::getPixelType() const {
    return pixelType;
}

/*-------------------------------------
 * Get the number of bits per pixel in the image.
-------------------------------------*/
inline unsigned imageResource::getBpp() const {
    return bitsPerPixel;
}

/*-------------------------------------
 * Get the OpenGL-compatible CPU-Side image format.
-------------------------------------*/
inline pixel_format_t imageResource::getInternalFormat() const {
    return intFormat;
}

/*-------------------------------------
 * Get the OpenGL-compatible GPU-Side image format.
-------------------------------------*/
inline pixel_layout_t imageResource::getExternalFormat() const {
    return extFormat;
}

} // end draw namespace
} // end ls namespace
