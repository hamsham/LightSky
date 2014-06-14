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
         * @param filename a c-style string containing the relative path name
         * to a file that should be loadable into memory.
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const char* filename) override;

        /**
         * Save an image file
         * @param filename a c-style string containing the relative path name
         * to a file that should be saved to the computer.
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const char*) const override;

        /**
         * Unload
         * Free all memory used by *this.
         */
        virtual void unload() override;

        /**
         * Get the raw, loaded, image data contained within *this.
         */
        virtual void* getData() const override;
        
        /**
         * Get the pixel size of the currently loaded image
         */
        math::vec2i getPixelSize() const {
            return imgSize;
        }
        
        /**
         * Get the format of the currently loaded image
         */
        unsigned getFormat() const {
            return pixelSize;
        }
        
        /**
         * Get the number of bits per pixel in the image
         * This can be 1, 2, 4, 8, 16, 24, 32, 48, 64, 96 128
         */
        unsigned getBpp() const {
            return bitsPerPixel;
        }
};

#endif	/* __LS_IMAGE_RESOURCE_H__ */

