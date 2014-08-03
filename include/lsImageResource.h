/* 
 * File:   imageResource.h
 * Author: hammy
 *
 * Created on February 2, 2014, 1:42 PM
 */

#ifndef __LS_IMAGE_RESOURCE_H__
#define	__LS_IMAGE_RESOURCE_H__

#include "lsSetup.h"
#include "lsResource.h"

/**
 * Enumerations for saving image files.
 */
enum class img_file_t {
    LS_IMG_BMP,
    LS_IMG_EXR,
    LS_IMG_GIF,
    LS_IMG_HDR,
    LS_IMG_ICO,
    LS_IMG_JPG,
    LS_IMG_J2K,
    LS_IMG_PNG, // default
    LS_IMG_PPM,
    LS_IMG_TGA,
    LS_IMG_TIF,
    LS_IMG_WBP,
    LS_IMG_XPM
};

/**
 * An image resource is a derivative of a resource object.
 * 
 * This class can load images using the FreeImage library, The pData member
 * contains raw texture data.
 * 
 * The inherited member "pData" will be reinterpreted as a pointer to a
 * FIBITMAP structure so as to make loading and saving easier to maintain.
 */
class lsImageResource final : public lsResource {
    private:
        /**
         * imgSize represents the pixel width & height of a loaded image
         */
        math::vec2i imgSize = {0};
        
        /**
         * Pixel format of the loaded image
         */
        unsigned pixelSize = 0;
        
        /**
         * Number of bits per pixel in the image
         */
        unsigned bitsPerPixel = 0;
        
        /**
         * Internal format of an image
         * 
         * This can be a pair of:
         * GL_R/GL_R
         * GL_RG/GL_RG
         * GL_RGB/GL_BGR
         * GL_RGBA/GL_BGRA
         * GL_RGB32F/GL_RGB32f
         * GL_RGBA32f/GL_RGBA32f
         */
        math::vec2i imgFormat = 0;

    public:
        /**
         * Constructor
         */
        constexpr lsImageResource() :
            lsResource{}
        {}
        
        /**
         * Copy Constructor
         * Attempts to copy all data from the source operand into *this.
         */
        lsImageResource(const lsImageResource&) = delete;
        
        /**
         * Move Operator
      `  * Moves data from the source operand into *this. No copies are
         * performed.
         */
        lsImageResource(lsImageResource&&);
        
        /**
         * Destructor
         * Calls "unload()" and releases all memory from *this.
         */
        virtual ~lsImageResource() {
            unload();
        }
        
        /**
         * Copy Operator
         * Attempts to copy all data from the source operand into *this.
         * @return a reference to *this.
         */
        lsImageResource& operator=(const lsImageResource&) = delete;
        
        /**
         * Move Operator
         * Moves all data from the source operand into *this. No copies are
         * performed.
         * @return a reference to *this.
         */
        lsImageResource& operator=(lsImageResource&&);

        /**
         * Load an image file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const char* filename) override;

        /**
         * Save an image file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const char*) const override;

        /**
         * Save an image file in a specific format
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        bool saveFile(const char*, img_file_t) const;

        /**
         * Unload
         * Free all memory used by *this.
         */
        virtual void unload() override;

        /**
         * Get the raw, loaded, image data contained within *this.
         * The underlying type has been cast from a FreeImage FIBITMAP*.
         * 
         * @return a void pointer to the raw image bits.
         */
        virtual void* getData() const override;
        
        /**
         * Get the pixel size of the currently loaded image
         * 
         * @return a 2D integer vector containing the width and height of the
         * loaded image, in pixels.
         */
        inline math::vec2i getPixelSize() const {
            return imgSize;
        }
        
        /**
         * Get the format of the currently loaded image
         */
        inline unsigned getFormat() const {
            return pixelSize;
        }
        
        /**
         * Get the number of bits per pixel in the image.
         * 
         * @return 0, 1, 2, 4, 8, 16, 24, 32, 48, 64, 96, or 128
         */
        inline unsigned getBpp() const {
            return bitsPerPixel;
        }
        
        inline math::vec2i getInternalFormat() const {
            return imgFormat;
        }
};

/*
 * saving
 */
inline bool lsImageResource::saveFile(const char* filename) const {
    return this->saveFile(filename, img_file_t::LS_IMG_PNG);
}

#endif	/* __LS_IMAGE_RESOURCE_H__ */

