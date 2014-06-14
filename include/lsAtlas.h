/* 
 * File:   texAtlas2d.h
 * Author: miles
 *
 * Created on February 16, 2014, 2:36 PM
 */

#ifndef __LS_GLYPH_ATLAS__
#define	__LS_GLYPH_ATLAS__

#include "lsFontResource.h"
#include "lsTexture.h"

/**
 * A glyph entry is s structure of arrays, with each element describing some
 * aspect of a portion of a texture atlas.
 */
struct lsAtlasEntry {
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

/**
 * A texture atlas contains a collection of textures which may be loaded into
 * GPU memory as a single texture.
 */
class lsAtlas {
    private:
        /**
         * Texture Rectangle used to store the texture atlas.
         */
        lsTexture atlasTex = {LS_TEX_RECT};
        
        /**
         * An array of atlas entries. The UVs for these entries is calculated
         * when loading the image data from a texture file.
         */
        lsAtlasEntry* entries = nullptr;
        
        /**
         * The number of entries in a texture atlas.
         */
        unsigned numEntries = 0;
        
    public:
        /**
         * Constructor
         */
        lsAtlas() {
        }
        
        /**
         * Copy constructor - DELETED
         */
        lsAtlas(const lsAtlas&) = delete;
        
        /**
         * Move Constructor
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        lsAtlas(lsAtlas&&);
        
        /**
         * Destructor.
         * Releases all data used by *this.
         */
        ~lsAtlas() {
            unload();
        }
        
        /**
         * Copy Operator - DELETED
         */
        lsAtlas& operator=(const lsAtlas&) = delete;
        
        /**
         * Move operator
         * Moves all data from the input parameter into *this.
         * 
         * @return A reference to *this
         */
        lsAtlas& operator=(lsAtlas&&);
        
        /**
         * Get a runtime ID associated with this object
         */
        inline unsigned getId() const {
            return atlasTex.getId();
        }
        
        /**
         * Stores the bitmap data located within a font file in *this as a
         * texture atlas.
         * 
         * @param A fully loaded font file
         * 
         * @return True if the data was sent to OpenGL. False if an error
         * occurred.
         */
        bool load(const lsFontResource&);
        
        /**
         * Frees all memory used by *this.
         */
        void unload() {
            atlasTex.terminate();
            
            delete [] entries;
            entries = nullptr;
            
            numEntries = 0;
        }
        
        /**
         * Retrieve the texture rectangle used by *this.
         */
        const lsTexture& getTexture() const {
            return atlasTex;
        }
        
        /**
         * Get the texture object associated with *this
         */
        lsTexture& getTexture() {
            return atlasTex;
        }
        
        /**
         * Retrieve the atlas entry specified by at a specific index.
         * Make sure that the atlas has been loaded before calling this.
         * 
         * Depending on the font loaded, this function will correspond to either
         * ASCII codes of UTF codes
         */
        lsAtlasEntry& getEntry(unsigned index) const {
            return entries[index];
        }
        
        /**
         * Retrieve the array of atlas entries contained within *this. 
         */
        lsAtlasEntry* getEntries() const {
            return entries;
        }
        
        /**
         * get the number of atlas entries currently loaded
         */
        unsigned getNumEntries() const {
            return numEntries;
        }
};

#endif	/* __LS_GLYPH_ATLAS__ */

