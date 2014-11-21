/* 
 * File:   draw/atlas.cpp
 * Author: Miles Lacey
 * 
 * Created on February 16, 2014, 2:36 PM
 */

#include <utility>

#include "lightsky/draw/atlas.h"
#include "lightsky/draw/color.h"

using ls::math::vec2;
using ls::math::vec2i;

namespace ls {
namespace draw {

/*
 * Destructor
 */
atlas::~atlas() {
    terminate();
}

/*
 * Constructor
 */
atlas::atlas() {
}

/*
 * Font Atlas Move constructor
 */
atlas::atlas(atlas&& a) :
    atlasTex{std::move(a.atlasTex)},
    entries{a.entries},
    numEntries{a.numEntries}
{
    a.entries = nullptr;
    a.numEntries = 0;
}

/*
 * Font Atlas move operator
 */
atlas& atlas::operator =(atlas&& a) {
    atlasTex = std::move(a.atlasTex);
    
    entries = a.entries;
    a.entries = nullptr;
    
    numEntries = a.numEntries;
    a.numEntries = 0;
    
    return *this;
}

/*
 * Store a fontFile's texture data on OpenGL server memory
 */
bool atlas::init(const fontResource& fr) {
    terminate();
    
    // calculate the size of the atlas. Cast like crazy.
    // Dimensions is the number of entries in the x/y directions
    const int dimensions = (int)std::sqrt((float)fr.getNumGlyphs());
    const vec2i&& maxGlyphSize = fr.getMaxGlyphSize();
    
    LS_LOG_MSG(
        "Attempting to load a font atlas.",
        "\n\tSupported X*Y Size: ", texture::getMaxTextureSize(),
        "\n\tGlyphs Per Row/Col: ", dimensions, " x ", dimensions,
        "\n\tTotal Glyph Count:  ", fr.getNumGlyphs(),
        "\n\tWidth Per Glyph:    ", maxGlyphSize[0],
        "\n\tHeight Per Glyph:   ", maxGlyphSize[1]
    );
    
    // prepare the array of atlas entries
    entries = new(std::nothrow) atlasEntry[fr.numGlyphs];
    if (entries == nullptr) {
        LS_LOG_ERR("\tUnable to generate an array of font atlas entries.\n");
        return false;
    }
    
    // Let OpenGL know that fonts only use 1-byte per pixel
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    if (!atlasTex.init(0, COLOR_FMT_R_8, maxGlyphSize*dimensions, COLOR_LAYOUT_R, COLOR_TYPE_UNSIGNED_BYTE, nullptr)) {
        LOG_GL_ERR();
        LS_LOG_ERR("\tAn error occurred while allocating space for a font atlas.\n");
        delete [] entries;
        entries = nullptr;
        return false;
    }
    
    LOG_GL_ERR();
    
    // Upload the data
    numEntries = fr.numGlyphs;
    int iter = 0;
    
    for (int x = 0; x < dimensions; ++x) {
        for (int y = 0; y < dimensions; ++y) {
            
            const glyph& pGlyph = fr.getGlyphs()[iter];
            atlasEntry& pEntry  = entries[iter];
            
            atlasTex.modify(
                vec2i{x*maxGlyphSize[0], y*maxGlyphSize[1]},
                pGlyph.size, COLOR_LAYOUT_GRAY, COLOR_TYPE_UNSIGNED_BYTE, pGlyph.pData
            );
            
            const float fDimension = (float)dimensions;
            
            // Texture atlases use a rectangle texture. no need to normalize the UVs
            // top-left uv coordinate for each glyph
            pEntry.uv[0] = vec2{(float)maxGlyphSize[0]*x, (float)maxGlyphSize[1]*y};
            
            // bottom left corner
            pEntry.uv[1] = pEntry.uv[0] + (vec2)pGlyph.size;

            // Add descriptor data for each glyoh.
            pEntry.advance = (vec2)pGlyph.advance;
            pEntry.advance /= fDimension;
            
            pEntry.bearing = (vec2)pGlyph.bearing;
            pEntry.bearing /= fDimension;
            
            pEntry.size = (vec2)pGlyph.size;
            pEntry.size /= fDimension;
            
            ++iter;
        }
    }
    
    atlasTex.setParameter(TEX_PARAM_WRAP_S, TEX_PARAM_CLAMP_BORDER);
    atlasTex.setParameter(TEX_PARAM_WRAP_T, TEX_PARAM_CLAMP_BORDER);
    atlasTex.unbind();
    LOG_GL_ERR();
    
    // Restore OpenGL's default pixel packing format 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    LOG_GL_ERR();
    
    LS_LOG_MSG("\tSuccessfully loaded a font atlas.\n");
    
    return true;
}
        
/*
 * Frees all memory used by *this.
 */
void atlas::terminate() {
    atlasTex.terminate();

    delete [] entries;
    entries = nullptr;

    numEntries = 0;
}

} // end draw namespace
} // end ls namespace
