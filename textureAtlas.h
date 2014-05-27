/* 
 * File:   texAtlas2d.h
 * Author: miles
 *
 * Created on February 16, 2014, 2:36 PM
 */

#ifndef __LS_TEXTURE_ATLAS_H__
#define	__LS_TEXTURE_ATLAS_H__

#include "fontResource.h"
#include "texture.h"

/**
 * A glyph entry is s structure of arrays, with each element describing some
 * aspect of a portion of a texture atlas.
 */
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

/**
 * A texture atlas contains a collection of textures which may be loaded into
 * GPU memory as a single texture.
 */
class textureAtlas {
    private:
        /**
         * Texture Rectangle used to store the texture atlas.
         */
        texture atlas = {tex_desc::TEX_RECT};
        
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
         * Constructor
         */
        textureAtlas() {
        }
        
        /**
         * Copy constructor - DELETED
         */
        textureAtlas(const textureAtlas&) = delete;
        
        /**
         * Move Constructor
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        textureAtlas(textureAtlas&&);
        
        /**
         * Destructor.
         * Releases all data used by *this.
         */
        ~textureAtlas() {
            unload();
        }
        
        /**
         * Copy Operator - DELETED
         */
        textureAtlas& operator=(const textureAtlas&) = delete;
        
        /**
         * Move operator
         * Moves all data from the input parameter into *this.
         * 
         * @return A reference to *this
         */
        textureAtlas& operator=(textureAtlas&&);
        
        /**
         * Stores the bitmap data located within a font file in *this as a
         * texture atlas.
         * 
         * @param A fully loaded font file
         * 
         * @return True if the data was sent to OpenGL. False if an error
         * occurred.
         */
        bool load(const fontResource&);
        
        /**
         * Frees all memory used by *this.
         */
        void unload() {
            atlas.terminate();
            
            delete [] entries;
            entries = nullptr;
            
            numEntries = 0;
        }
        
        /**
         * Retrieve the texture rectangle used by *this.
         */
        const texture& getTexture() const {
            return atlas;
        }
        
        /**
         * Get the texture object associated with *this
         */
        texture& getTexture() {
            return atlas;
        }
        
        /**
         * Retrieve the atlas entry specified by at a specific index.
         * Make sure that the atlas has been loaded before calling this.
         * 
         * Depending on the font loaded, this function will correspond to either
         * ASCII codes of UTF codes
         */
        atlasEntry& getEntry(unsigned index) const {
            return entries[index];
        }
        
        /**
         * Retrieve the array of atlas entries contained within *this. 
         */
        atlasEntry* getEntries() const {
            return entries;
        }
        
        /**
         * get the number of atlas entries currently loaded
         */
        unsigned getNumEntries() const {
            return numEntries;
        }
};

#endif	/* __LS_TEXTURE_ATLAS_H__ */

