/* 
 * File:   lsFontResource.h
 * Author: miles
 *
 * Created on February 16, 2014, 2:36 PM
 */

#ifndef __LS_FONT_RESOURCE_H__
#define	__LS_FONT_RESOURCE_H__

#include "lsSetup.h"
#include "lsResource.h"

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
enum : int {
    LS_DEFAULT_FONT_SIZE = 72
};

//-----------------------------------------------------------------------------
//      Forward Declarations
//-----------------------------------------------------------------------------
struct FT_FaceRec_;

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * Font Metrics
 * 
 * This contains the basic data for each individual glyph in a font.
 */
struct lsGlyph {
    math::vec2i size = {0};
    math::vec2i advance = {0};
    math::vec2i bearing = {0};
    char* pData = nullptr;
    
    ~lsGlyph() {
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
class lsFontResource final : public lsResource {
    friend class lsAtlas;
    
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
        lsFontResource();
        
        /**
         * Copy Constructor
         * Attempts to copy the resources located within the parameter "f."
         * This function delegates all responsibility to "setData()."
         */
        lsFontResource(const lsFontResource&) = delete;
        /**
         * Move Constructor
         * Attempts to move all resources from the input argument into *this.
         * No deletions are made.
         */
        lsFontResource(lsFontResource&&);
        
        /**
         * Destructor
         * Calls "unload()" and releases all memory used by *this.
         */
        virtual ~lsFontResource();
        
        /**
         * Copy Operator
         * Attempts to copy the resources contained within the parameter "f."
         * This function delegates all responsibility to "setData()."
         */
        lsFontResource& operator=(const lsFontResource&) = delete;
        
        /**
         * Move Operator
         * Attempts to move all resources from the input argument into *this.
         * No deletions are made.
         */
        lsFontResource& operator=(lsFontResource&&);

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
        virtual bool loadFile(const char* filename) override;

        /**
         * Save a file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const char*) const override;

        /**
         * Unload
         * Free all memory used by *this.
         */
        virtual void unload() override;
        
        /**
         * Get the size of the currently loaded fonts
         */
        unsigned getFontSize() const;
        
        /**
         * Get the array of glyphs used by *this
         */
        const lsGlyph* getGlyphs() const;
        
        /**
         * Get the number of glyphs that have been loaded
         */
        unsigned getNumGlyphs() const;
        
        /**
         * Get the size of the widest glyph
         */
        math::vec2i getMaxGlyphSize() const;
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Load a font file using the default font size.
 */
inline bool lsFontResource::loadFile(const char* filename) {
    return loadFile(filename, LS_DEFAULT_FONT_SIZE);
}

/*
 * Get the size of the currently loaded fonts
 */
inline unsigned lsFontResource::getFontSize() const {
    return glyphSize;
}

/*
 * Get the array of glyphs used by *this
 */
inline const lsGlyph* lsFontResource::getGlyphs() const {
    return reinterpret_cast<lsGlyph*>(pData);
}

/*
 * Get the number of glyphs that have been loaded
 */
inline unsigned lsFontResource::getNumGlyphs() const {
    return numGlyphs;
}

/*
 * Get the size of the widest glyph
 */
inline math::vec2i lsFontResource::getMaxGlyphSize() const {
    return maxGlyphSize;
}

#endif	/* __LS_FONT_RESOURCE_H__ */

