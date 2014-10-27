/* 
 * File:   draw/atlas.h
 * Author: Miles Lacey
 *
 * Created on February 16, 2014, 2:36 PM
 */

#ifndef __LS_DRAW_ATLAS_H__
#define	__LS_DRAW_ATLAS_H__

#include "lightsky/draw/fontResource.h"
#include "lightsky/draw/texture.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * @brief atlasEntry
 * 
 * An atlasEntry contains the coordinates of individual glyphs within a texture
 * atlas.
-----------------------------------------------------------------------------*/
struct atlasEntry {
    /**
     * Size corresponds to the vertex width and height of a glyph.
     */
    math::vec2 size;
    
    /**
     * Advance is mostly used for font kerning
     */
    math::vec2 advance;
    
    /**
     * Bearing is mostly used for font kerning.
     */
    math::vec2 bearing;
    
    /**
     * UV is an array representing the top-left and bottom-right portions of a
     * glyph (an element in a texture atlas).
     */
    math::vec2 uv[2];
};

/**----------------------------------------------------------------------------
 * @brief Texture Atlas Class
 * 
 * A texture atlas contains a collection of textures which may be loaded into
 * GPU memory as a single texture.
-----------------------------------------------------------------------------*/
class atlas {
    private:
        /**
         * Texture Rectangle used to store the texture atlas.
         */
        texture atlasTex = {LS_TEX_RECT};
        
        /**
         * An array of atlas entries. The UVs for these entries is calculated
         * when loading the image data from a texture file.
         */
        atlasEntry* entries = nullptr;
        
        /**
         * The number of entries in a texture atlas.
         */
        unsigned numEntries = 0;
        
    public:
        /**
         * @brief Constructor
         */
        atlas();
        
        /**
         * @brief Copy constructor - DELETED
         */
        atlas(const atlas&) = delete;
        
        /**
         * @brief Move Constructor
         * 
         * @param a
         * An r-value reference to a temporary atlas object.
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        atlas(atlas&& a);
        
        /**
         * @brief Destructor
         * 
         * Releases all data used by *this.
         */
        ~atlas();
        
        /**
         * @brief Copy Operator - DELETED
         */
        atlas& operator=(const atlas&) = delete;
        
        /**
         * @brief Move operator
         * 
         * Moves all data from the input parameter into *this.
         * 
         * @param a
         * An r-value reference to a temporary atlas object.
         * 
         * @return A reference to *this
         */
        atlas& operator=(atlas&& a);
        
        /**
         * Get a runtime ID associated with this object
         * 
         * @return The GPU-Assigned ID that is used by this object's internal
         * texture atlas.
         */
        unsigned getId() const;
        
        /**
         * Stores the bitmap data located within a font file in *this as a
         * texture atlas.
         * 
         * @param fr
         * A fully loaded font file
         * 
         * @return True if the data was sent to OpenGL. False if an error
         * occurred.
         */
        bool init(const fontResource& fr);
        
        /**
         * Frees all memory used by *this.
         */
        void terminate();
        
        /**
         * Retrieve the texture rectangle used by *this.
         * 
         * @return A constant reference to the internal texture used by *this.
         */
        const texture& getTexture() const;
        
        /**
         * Get the texture object associated with *this
         * 
         * @return A reference to the internal texture used by *this.
         */
        texture& getTexture();
        
        /**
         * Retrieve the atlas entry specified by at a specific index.
         * Make sure that the atlas has been loaded before calling this.
         * 
         * Depending on the font loaded, this function will correspond to either
         * ASCII codes of UTF codes
         * 
         * @param index
         * An unsigned integral type, representing the index of a desired glyph
         * within *this object's glyph table.
         * 
         * @return A constant reference to a single glyph within the texture
         * atlas.
         */
        const atlasEntry& getEntry(unsigned index) const;
        
        /**
         * Retrieve the array of atlas entries contained within *this.
         * 
         * @return A constant pointer to the the internal array of atlas glyphs
         */
        const atlasEntry* getEntries() const;
        
        /**
         * Get the number of atlas entries currently loaded
         */
        unsigned getNumEntries() const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/atlas_impl.h"

#endif	/* __LS_DRAW_ATLAS_H__ */

