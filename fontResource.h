/* 
 * File:   fontResource.h
 * Author: miles
 *
 * Created on February 16, 2014, 2:36 PM
 */

#ifndef __LS_FONT_RESOURCE_H__
#define	__LS_FONT_RESOURCE_H__

#include "main.h"
#include "resource.h"

#ifndef LS_DEFAULT_FONT_SIZE
    #define LS_DEFAULT_FONT_SIZE 72
#endif

/*
 * Forward Declarations for FreeType structures
 */
struct FT_FaceRec_;

/**
 * Font Metrics
 * 
 * This contains the basic data for each individual glyph in a font.
 */
struct glyph {
    math::vec2i size = {0};
    math::vec2i advance = {0};
    math::vec2i bearing = {0};
    char* pData = nullptr;
    
    ~glyph() {
        delete [] pData;
    }
};

/**
 * Font loader
 * 
 * A font loader can load TTF and OTF fonts by proxy of the FreeType library.
 * When using the getData() method, the returned pointer should be type casted
 * to "const glyph*".
 */
class fontResource final : public resource {
    friend class textureAtlas;
    
    private:
        /**
         * Number of loaded glyphs
         */
        unsigned numGlyphs = 0;
        
        /**
         * Contains the currently loaded font's glyph size
         */
        unsigned glyphSize = 0;
        
        /**
         * Size of the largest glyph
         */
        math::vec2i maxGlyphSize = {0, 0};
        
        /**
         * Internal loading function for all glyphs
         */
        bool loadGlyphs(FT_FaceRec_*);
        
    public:
        /**
         * Constructor
         * Initialized all variables to 0 values.
         */
        constexpr fontResource() :
            resource{}
        {}
        
        /**
         * Copy Constructor
         * Attempts to copy the resources located within the parameter "f."
         * This function delegates all responsibility to "setData()."
         */
        fontResource(const fontResource&) = delete;
        /**
         * Move Constructor
         * Attempts to move all resources from the input argument into *this.
         * No deletions are made.
         */
        fontResource(fontResource&&);
        
        /**
         * Destructor
         * Calls "unload()" and releases all memory used by *this.
         */
        virtual ~fontResource() {
            unload();
        }
        
        /**
         * Copy Operator
         * Attempts to copy the resources contained within the parameter "f."
         * This function delegates all responsibility to "setData()."
         */
        fontResource& operator=(const fontResource&) = delete;
        
        /**
         * Move Operator
         * Attempts to move all resources from the input argument into *this.
         * No deletions are made.
         */
        fontResource& operator=(fontResource&&);

        /**
         * Load a font file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be loadable into memory.
         * 
         * @param the name of the file to be loaded.
         * 
         * @param the size, in pixels, that each glyph should be.
         * 
         * @return true if the font was successfully loaded. False if not.
         */
        bool loadFile(const char* filename, unsigned pixelSize);

        /**
         * Load a font file using the default font size.
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be loadable into memory.
         * 
         * @return true if the font was successfully loaded. False if not.
         */
        virtual bool loadFile(const char* filename) override {
            return loadFile(filename, LS_DEFAULT_FONT_SIZE);
        }

        /**
         * Save a file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const char*) const override {
            return false;
        }

        /**
         * Unload
         * Free all memory used by *this.
         */
        virtual void unload() override;
        
        /**
         * Get the size of the currently loaded fonts
         */
        unsigned getFontSize() const {
            return glyphSize;
        }
        
        /**
         * Get the array of glyphs used by *this
         */
        const glyph* getGlyphs() const {
            return reinterpret_cast<glyph*>(pData);
        }
        
        /**
         * Get the number of glyphs that have been loaded
         */
        unsigned getNumGlyphs() const {
            return numGlyphs;
        }
        
        /**
         * Get the size of the widest glyph
         */
        math::vec2i getMaxGlyphSize() const {
            return maxGlyphSize;
        }
};

#endif	/* __LS_FONT_RESOURCE_H__ */

