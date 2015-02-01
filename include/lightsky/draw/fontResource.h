/* 
 * File:   draw/fontResource.h
 * Author: Miles Lacey
 *
 * Created on February 16, 2014, 2:36 PM
 */

#ifndef __LS_FONT_RESOURCE_H__
#define	__LS_FONT_RESOURCE_H__

#include <string>

#include "lightsky/draw/setup.h"
#include "lightsky/utils/resource.h"

/*-----------------------------------------------------------------------------
    Forward Declarations
-----------------------------------------------------------------------------*/
struct FT_FaceRec_;

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * @brief Font Metrics
 * 
 * This contains the basic data for each individual glyph in a font.
-----------------------------------------------------------------------------*/
struct glyph {
    math::vec2i size = {0};
    math::vec2i advance = {0};
    math::vec2i bearing = {0};
    char* pData = nullptr;
    
    ~glyph() {
        delete [] pData;
    }
};

/**----------------------------------------------------------------------------
 * @brief Font File loader
 * 
 * A font loader can load TTF and OTF fonts by proxy of the FreeType library.
 * When using the getData() method, the returned pointer should be type casted
 * to "const glyph*".
-----------------------------------------------------------------------------*/
class fontResource final : public ls::utils::resource {
    friend class atlas;
    
    public:
        /**
         * Default font size (as DPI) of fonts loaded from a file.
         */
        enum : unsigned {
            FONT_SIZE_LOW       = 48,
            FONT_SIZE_MEDIUM    = 72,
            FONT_SIZE_HIGH      = 96,

            FONT_SIZE_DEFAULT   = 72
        };
    
    private:
        /**
         * Number of loaded glyphs
         */
        unsigned numGlyphs = 0;
        
        /**
         * Contains the currently loaded font's glyph size
         */
        unsigned glyphSize = FONT_SIZE_DEFAULT;
        
        /**
         * Size of the largest glyph
         */
        math::vec2i maxGlyphSize = {0, 0};
        
        /**
         * @brief Internal loading function for all glyphs.
         * 
         * @param ftFace
         * A pointer to a FreeType font face array. This is used internally to
         * convert True-Type font metrics into a bitmap which can be sent to
         * OpenGL.
         * 
         * @return TRUE if a font's glyphs were successfully loaded from a file
         * by FreeType, FALSE if not.
         */
        bool loadGlyphs(FT_FaceRec_* ftFace);
        
    public:
        /**
         * @brief Constructor
         * 
         * Initialized all variables to 0 values.
         */
        fontResource();
        
        /**
         * Copy Constructor - DELETED
         */
        fontResource(const fontResource&) = delete;
        /**
         * @brief Move Constructor
         * 
         * Attempts to move all resources from the input argument into *this.
         * No deletions are made.
         * 
         * @param fr
         * An r-value reference to another fontResource object.
         */
        fontResource(fontResource&& fr);
        
        /**
         * @brief Destructor
         * 
         * Calls "unload()" and releases all memory used by *this.
         */
        virtual ~fontResource() override;
        
        /**
         * @brief Copy Operator - DELETED
         */
        fontResource& operator=(const fontResource&) = delete;
        
        /**
         * @brief Move Operator
         * 
         * Attempts to move all resources from the input argument into *this.
         * No copies are made.
         * 
         * @param fr
         * An r-value reference to another fontResource object.
         * 
         * @return a reference to *this.
         */
        fontResource& operator=(fontResource&& fr);

        /**
         * @brief Load a font file
         * 
         * This method will load a font file using a specified pixel size.
         * 
         * @param filename
         * A c-style string containing the relative path name
         * to a file that should be loaded into memory.
         * 
         * @param pixelSize
         * The size, in pixels, that each glyph should be.
         * 
         * @return true if the font was successfully loaded. False if not.
         */
        bool loadFile(const std::string& filename, unsigned pixelSize);

        /**
         * @brief Load a font file
         * 
         * This method will load a font file using a specified pixel size.
         * 
         * @param filename
         * A c-style string containing the relative path name
         * to a file that should be loaded into memory.
         * 
         * @param pixelSize
         * the size, in pixels, that each glyph should be.
         * 
         * @return true if the font was successfully loaded. False if not.
         */
        bool loadFile(const std::wstring& filename, unsigned pixelSize);

        /**
         * @brief Load a font file
         * 
         * This method will load a font file using the default font size.
         * 
         * @param filename
         * A c-style string containing the relative path name
         * to a file that should be loaded into memory.
         * 
         * @return true if the font was successfully loaded. False if not.
         */
        virtual bool loadFile(const std::string& filename) override;

        /**
         * @brief Load a font file
         * 
         * This method will load a font file using the default font size.
         * 
         * @param filename
         * A c-style string containing the relative path name
         * to a file that should be loaded into memory.
         * 
         * @return true if the font was successfully loaded. False if not.
         */
        virtual bool loadFile(const std::wstring& filename) override;

        /**
         * @brief Save a file
         * 
         * This method will save a font to a file indicated by the specified
         * path name.
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const std::string& filename) const override;

        /**
         * @brief Unload
         * 
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
        const glyph* getGlyphs() const;
        
        /**
         * Get the number of glyphs that have been loaded
         */
        unsigned getNumGlyphs() const;
        
        /**
         * Get the size of the widest glyph
         */
        math::vec2i getMaxGlyphSize() const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/fontResource_impl.h"

#endif	/* __LS_FONT_RESOURCE_H__ */
