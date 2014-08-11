/* 
 * File:   lsImageResource.h
 * Author: hammy
 *
 * Created on February 2, 2014, 1:42 PM
 */

#ifndef __LS_IMAGE_RESOURCE_H__
#define	__LS_IMAGE_RESOURCE_H__

#include <string>

#include "lsColor.h"
#include "lsResource.h"
#include "lsSetup.h"

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
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
        ls_color_type_t pixelType = LS_DEFAULT_COLOR_TYPE;
        
        /**
         * Number of bits per pixel in the image
         */
        unsigned bitsPerPixel = 0;
        
        /**
         * CPU-Side format of an image
         * 
         * This can be any of the following:
         * LS_GRAY_N
         * LS_RG_N
         * LS_RGB_N
         * LS_RGBA_N
         * LS_RGB_32F
         * LS_RGBA_32F
         * where N is 8, 16, or 32
         */
        ls_pixel_format_t intFormat = LS_DEFAULT_PIXEL_FORMAT;
        
        
        /**
         * CPU-Side format of an image
         * 
         * This can be any of the following:
         * LS_GRAY
         * LS_RG
         * LS_RGB
         * LS_RGBA
         * LS_RGB16F
         * LS_RGBA32F
         * LS_RGB16F
         * LS_RGBA32F
         */
        ls_pixel_layout_t extFormat = LS_DEFAULT_PIXEL_LAYOUT;

    public:
        /**
         * Constructor
         */
        lsImageResource();
        
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
        virtual ~lsImageResource();
        
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
         * @param filename
         * A string object containing the relative path name to a file that
         * should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const std::string& filename) override;

        /**
         * Save an image file
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const std::string& filename) const override;

        /**
         * Save an image file in a specific format
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        bool saveFile(const std::string&, img_file_t) const;

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
        math::vec2i getPixelSize() const;
        
        /**
         * Get the format of the currently loaded image.
         * For example, LS_UNSIGNED_BYTE, LS_INT, LS_FLOAT, etc.
         */
        ls_color_type_t getPixelType() const;
        
        /**
         * Get the number of bits per pixel in the image.
         * 
         * @return 0, 1, 2, 4, 8, 16, 24, 32, 48, 64, 96, or 128
         */
        unsigned getBpp() const;
        
        /**
         * Get the OpenGL-compatible CPU-Side image format.
         * 
         * @return An enumeration containing image format information that can
         * be used when setting up textures in OpenGL.
         */
        ls_pixel_format_t getInternalFormat() const;
        
        /**
         * Get the OpenGL-compatible CPU-Side/GPU-Side image format pair.
         * 
         * @return An enumeration containing image format information that can
         * be used when setting up textures in OpenGL.
         */
        ls_pixel_layout_t getExternalFormat() const;
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Saving Data
 */
inline bool lsImageResource::saveFile(const std::string& filename) const {
    return saveFile(filename, img_file_t::LS_IMG_PNG);
}

/*
 * Get the pixel size of the currently loaded image
 */
inline math::vec2i lsImageResource::getPixelSize() const {
    return imgSize;
}

/*
 * Get the GPU-compatible format of the currently loaded image
 */
inline ls_color_type_t lsImageResource::getPixelType() const {
    return pixelType;
}

/*
 * Get the number of bits per pixel in the image.
 */
inline unsigned lsImageResource::getBpp() const {
    return bitsPerPixel;
}

/*
 * Get the OpenGL-compatible CPU-Side image format.
 */
inline ls_pixel_format_t lsImageResource::getInternalFormat() const {
    return intFormat;
}

/*
 * Get the OpenGL-compatible GPU-Side image format.
 */
inline ls_pixel_layout_t lsImageResource::getExternalFormat() const {
    return extFormat;
}

#endif	/* __LS_IMAGE_RESOURCE_H__ */

