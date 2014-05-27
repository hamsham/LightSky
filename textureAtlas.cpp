/* 
 * File:   textureAtlas.cpp
 * Author: miles
 * 
 * Created on February 16, 2014, 2:36 PM
 */

#include <utility>
#include "textureAtlas.h"

using math::vec2;
using math::vec2i;

/*
 * Font Atlas Move constructor
 */
textureAtlas::textureAtlas(textureAtlas&& fa) :
    atlas{std::move(fa.atlas)},
    entries{fa.entries},
    numEntries{fa.numEntries}
{
    fa.entries = nullptr;
    fa.numEntries = 0;
}

/*
 * Font Atlas move operator
 */
textureAtlas& textureAtlas::operator =(textureAtlas&& fa) {
    atlas = std::move(fa.atlas);
    
    entries = fa.entries;
    fa.entries = nullptr;
    
    numEntries = fa.numEntries;
    fa.numEntries = 0;
    
    return *this;
}

/*
 * Store a fontFile's texture data on OpenGL server memory
 */
bool textureAtlas::load(const fontResource& ff) {
    unload();
    
    // calculate the size of the atlas. Cast like crazy.
    // Dimensions is the number of entries in the x/y directions
    const int dimensions = (int)std::sqrt((float)ff.getNumGlyphs());
    const vec2i&& maxGlyphSize = ff.getMaxGlyphSize();
    
    LOG_MSG(
        "Attempting to load a font atlas.",
        "\n\tSupported X*Y Size: ", texture::getMaxTextureSize(),
        "\n\tGlyphs Per Row/Col: ", dimensions, " x ", dimensions,
        "\n\tTotal Glyph Count:  ", ff.getNumGlyphs(),
        "\n\tWidth Per Glyph:    ", maxGlyphSize[0],
        "\n\tHeight Per Glyph:   ", maxGlyphSize[1]
    );
    
    // prepare the array of atlas entries
    entries = new(std::nothrow) atlasEntry[ff.numGlyphs];
    if (entries == nullptr) {
        LOG_ERR("Unable to generate an array of font atlas entries.");
        return false;
    }
    
    if (!atlas.init(0, GL_RED, maxGlyphSize*dimensions, GL_RED, GL_UNSIGNED_BYTE, nullptr)) {
        LOG_GL_ERR();
        LOG_ERR("An error occurred while allocating space for a font atlas.");
        delete [] entries;
        entries = nullptr;
        return false;
    }
    
    // Let OpenGL know that fonts only use 1-bytes per pixel
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    LOG_GL_ERR();
    
    // Upload the data
    numEntries = ff.numGlyphs;
    int iter = 0;
    
    for (int x = 0; x < dimensions; ++x) {
        for (int y = 0; y < dimensions; ++y) {
            
            const glyph& pGlyph = ff.getGlyphs()[iter];
            atlasEntry& pEntry  = entries[iter];
            
            atlas.modify(
                vec2i{x*maxGlyphSize[0], y*maxGlyphSize[1]},
                pGlyph.size, GL_RED, GL_UNSIGNED_BYTE, pGlyph.pData
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
    
    atlas.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    atlas.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    atlas.unbind();
    LOG_GL_ERR();
    
    // Restore OpenGL's default pixel packing format 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    LOG_GL_ERR();
    
    LOG_MSG("Successfully loaded a font atlas.");
    
    return true;
}
