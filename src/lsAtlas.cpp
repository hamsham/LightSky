/* 
 * File:   lsAtlas.cpp
 * Author: miles
 * 
 * Created on February 16, 2014, 2:36 PM
 */

#include <utility>

#include "lsAtlas.h"
#include "lsColor.h"

using math::vec2;
using math::vec2i;

/*
 * Destructor
 */
lsAtlas::~lsAtlas() {
    terminate();
}

/*
 * Constructor
 */
lsAtlas::lsAtlas() {
}

/*
 * Font Atlas Move constructor
 */
lsAtlas::lsAtlas(lsAtlas&& fa) :
    atlasTex{std::move(fa.atlasTex)},
    entries{fa.entries},
    numEntries{fa.numEntries}
{
    fa.entries = nullptr;
    fa.numEntries = 0;
}

/*
 * Font Atlas move operator
 */
lsAtlas& lsAtlas::operator =(lsAtlas&& fa) {
    atlasTex = std::move(fa.atlasTex);
    
    entries = fa.entries;
    fa.entries = nullptr;
    
    numEntries = fa.numEntries;
    fa.numEntries = 0;
    
    return *this;
}

/*
 * Store a fontFile's texture data on OpenGL server memory
 */
bool lsAtlas::init(const lsFontResource& ff) {
    terminate();
    
    // calculate the size of the atlas. Cast like crazy.
    // Dimensions is the number of entries in the x/y directions
    const int dimensions = (int)std::sqrt((float)ff.getNumGlyphs());
    const vec2i&& maxGlyphSize = ff.getMaxGlyphSize();
    
    LS_LOG_MSG(
        "Attempting to load a font atlas.",
        "\n\tSupported X*Y Size: ", lsTexture::getMaxTextureSize(),
        "\n\tGlyphs Per Row/Col: ", dimensions, " x ", dimensions,
        "\n\tTotal Glyph Count:  ", ff.getNumGlyphs(),
        "\n\tWidth Per Glyph:    ", maxGlyphSize[0],
        "\n\tHeight Per Glyph:   ", maxGlyphSize[1]
    );
    
    // prepare the array of atlas entries
    entries = new(std::nothrow) lsAtlasEntry[ff.numGlyphs];
    if (entries == nullptr) {
        LS_LOG_ERR("\tUnable to generate an array of font atlas entries.\n");
        return false;
    }
    
    // Let OpenGL know that fonts only use 1-byte per pixel
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    if (!atlasTex.init(0, LS_R_8, maxGlyphSize*dimensions, LS_R, LS_UNSIGNED_BYTE, nullptr)) {
        LOG_GL_ERR();
        LS_LOG_ERR("\tAn error occurred while allocating space for a font atlas.\n");
        delete [] entries;
        entries = nullptr;
        return false;
    }
    
    LOG_GL_ERR();
    
    // Upload the data
    numEntries = ff.numGlyphs;
    int iter = 0;
    
    for (int x = 0; x < dimensions; ++x) {
        for (int y = 0; y < dimensions; ++y) {
            
            const lsGlyph& pGlyph = ff.getGlyphs()[iter];
            lsAtlasEntry& pEntry  = entries[iter];
            
            atlasTex.modify(
                vec2i{x*maxGlyphSize[0], y*maxGlyphSize[1]},
                pGlyph.size, LS_GRAY, LS_UNSIGNED_BYTE, pGlyph.pData
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
    
    atlasTex.setParameter(LS_TEX_WRAP_S, LS_TEX_CLAMP_BORDER);
    atlasTex.setParameter(LS_TEX_WRAP_T, LS_TEX_CLAMP_BORDER);
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
void lsAtlas::terminate() {
    atlasTex.terminate();

    delete [] entries;
    entries = nullptr;

    numEntries = 0;
}
