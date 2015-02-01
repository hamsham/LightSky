
namespace ls {
namespace draw {

/*-------------------------------------
 * Load a font file using the default font size.
-------------------------------------*/
inline bool fontResource::loadFile(const std::wstring& filename, unsigned pixelSize) {
    return loadFile(ls::utils::convertWtoMb(filename), pixelSize);
}
 
/*-------------------------------------
 * Load a font file using the default font size.
-------------------------------------*/
inline bool fontResource::loadFile(const std::wstring& filename) {
    return loadFile(ls::utils::convertWtoMb(filename));
}

/*-------------------------------------
 * Load a font file using the default font size.
-------------------------------------*/
inline bool fontResource::loadFile(const std::string& filename) {
    return loadFile(filename, FONT_SIZE_DEFAULT);
}

/*-------------------------------------
 * Get the size of the currently loaded fonts
-------------------------------------*/
inline unsigned fontResource::getFontSize() const {
    return glyphSize;
}

/*-------------------------------------
 * Get the array of glyphs used by *this
-------------------------------------*/
inline const glyph* fontResource::getGlyphs() const {
    return reinterpret_cast<glyph*>(pData);
}

/*-------------------------------------
 * Get the number of glyphs that have been loaded
-------------------------------------*/
inline unsigned fontResource::getNumGlyphs() const {
    return numGlyphs;
}

/*-------------------------------------
 * Get the size of the widest glyph
-------------------------------------*/
inline math::vec2i fontResource::getMaxGlyphSize() const {
    return maxGlyphSize;
}

} // end draw namespace
} // end ls namespace
