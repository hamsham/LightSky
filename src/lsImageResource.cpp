/* 
 * File:   imageResource.cpp
 * Author: hammy
 * 
 * Created on February 2, 2014, 1:42 PM
 */

#include <unordered_map>
#include <utility> // std::move
#include <Gl/glew.h>
#include <FreeImage.h>
#include <string>

#include "lsSetup.h"
#include "lsImageResource.h"

/******************************************************************************
 * Utilities
*******************************************************************************/
/*
 * FreeImage error handler message
 */
#ifdef LS_DEBUG
    void printImageLoadError(FREE_IMAGE_FORMAT fif, const char* msg) {
        LS_LOG_ERR(
            "\tAn image file error has occurred:",
            "\n\tFormat: ", FreeImage_GetFormatFromFIF(fif),
            "\n\t", msg, "."
        );
    }
#else
    void printImageLoadError(FREE_IMAGE_FORMAT, const char*) {}
#endif

/*
 * Deduce an image's file format
 */
FREE_IMAGE_FORMAT deduceImageFormat(const char* filename) {
	FREE_IMAGE_FORMAT outFormat = FreeImage_GetFileType(filename, 0);
	if (outFormat == FIF_UNKNOWN) {
		outFormat = FreeImage_GetFIFFromFilename(filename);
    }
    return outFormat;
}

/*
 * Predefined image flags
 */
int getImageFlags(FREE_IMAGE_FORMAT inFormat) {
	switch(inFormat) {
		case FIF_JPEG:  return JPEG_ACCURATE | JPEG_EXIFROTATE;
		case FIF_TARGA: return TARGA_LOAD_RGB888;
		case FIF_ICO:   return ICO_MAKEALPHA;
		default:        return 0;
	}
}

/*
 * Get an image's pixel format, combined with its bits per pixel
 */
unsigned getBitmapSize(FIBITMAP* pImg) {
    // Get the data type of the image. Convert to an internal format
    const int storageType = FreeImage_GetImageType(pImg);
    unsigned dataType = 0;
    
    if (storageType == FIT_UNKNOWN
    ||  storageType == FIT_DOUBLE
    ||  storageType == FIT_COMPLEX
    ) {
        return 0;
    }
    
    switch(storageType) {
        // n-bit char
        case FIT_BITMAP:
            LS_LOG_MSG("\tImage pixel type: BYTE");
            dataType = GL_UNSIGNED_BYTE;
            break;
            
        // 16-bit short
        case FIT_INT16:
            dataType = GL_SHORT;
            LS_LOG_MSG("\tImage pixel type: SHORT");
            break;
                
        case FIT_UINT16:
            dataType = GL_UNSIGNED_SHORT;
            LS_LOG_MSG("\tImage pixel type: UNSIGNED SHORT");
            break;
        
        // 32-bit int
        case FIT_INT32:
            dataType = GL_INT;
            LS_LOG_MSG("\tImage pixel type: INT");
            break;
                
        case FIT_UINT32:
            dataType = GL_UNSIGNED_INT;
            LS_LOG_MSG("\tImage pixel type: UNSIGNED INT");
            break;
        
        // 96-bit float
        case FIT_RGBF:
        // 128-bit float
        case FIT_RGBAF:
            dataType = GL_FLOAT;
            LS_LOG_MSG("\tImage pixel type: FLOAT");
            break;
        
        // unknown
        default:
            return 0;
            LS_LOG_MSG("\tImage pixel type: INVALID");
            break;
    }
    
    return dataType;
}

math::vec2i getPixelFormat(FIBITMAP* pImg, unsigned bpp) {
    LS_LOG_MSG("\tImage Bits Per Pixel: ", bpp);
    
    // Get the data type of the image. Convert to an internal format
    const FREE_IMAGE_TYPE dataType = FreeImage_GetImageType(pImg);
    
    if (dataType == FIT_BITMAP) {
        if (bpp == 8)   return math::vec2i{GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT};
        if (bpp == 16)  return math::vec2i{GL_RG8, GL_RG};
        if (bpp == 24)  return math::vec2i{GL_RGB8, GL_BGR};
        if (bpp == 32)  return math::vec2i{GL_RGBA8, GL_BGRA};
    }
    else if (dataType == FIT_INT16) {
        if (bpp == 16)  return math::vec2i{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT};
        if (bpp == 32)  return math::vec2i{GL_RG16I, GL_RG};
        if (bpp == 48)  return math::vec2i{GL_RGB16I, GL_BGR};
        if (bpp == 64)  return math::vec2i{GL_RGBA16I, GL_BGRA};
    }
    else if (dataType == FIT_UINT16) {
        if (bpp == 16)  return math::vec2i{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT};
        if (bpp == 32)  return math::vec2i{GL_RG16UI, GL_RG};
        if (bpp == 48)  return math::vec2i{GL_RGB16UI, GL_BGR};
        if (bpp == 64)  return math::vec2i{GL_RGBA16UI, GL_BGRA};
    }
    else if (dataType == FIT_INT32) {
        if (bpp == 32)  return math::vec2i{GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT};
        if (bpp == 64)  return math::vec2i{GL_RG32I, GL_RG};
        if (bpp == 96)  return math::vec2i{GL_RGB32I, GL_BGR};
        if (bpp == 128) return math::vec2i{GL_RGBA32I, GL_BGRA};
    }
    else if (dataType == FIT_UINT32) {
        if (bpp == 32)  return math::vec2i{GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT};
        if (bpp == 64)  return math::vec2i{GL_RG32UI, GL_RG};
        if (bpp == 96)  return math::vec2i{GL_RGB32UI, GL_BGR};
        if (bpp == 128) return math::vec2i{GL_RGBA32UI, GL_BGRA};
    }
    else if (dataType == FIT_FLOAT) {
        if (bpp == 32)  return math::vec2i{GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT};
        if (bpp == 64)  return math::vec2i{GL_RG32F, GL_RG};
        if (bpp == 96)  return math::vec2i{GL_RGB32F, GL_BGR};
        if (bpp == 128) return math::vec2i{GL_RGBA32F, GL_BGRA};
    }
    else if (dataType == FIT_RGB16) {
        return math::vec2i{GL_RGB16F, GL_BGR};
    }
    else if (dataType == FIT_RGBA16) {
        return math::vec2i{GL_RGBA16F, GL_BGRA};
    }
    else if (dataType == FIT_RGBF) {
        return math::vec2i{GL_RGB32F, GL_BGR};
    }
    else if (dataType == FIT_RGBAF) {
        return math::vec2i{GL_RGBA32F, GL_BGRA};
    }
    
    return math::vec2i{0,0};
}

/******************************************************************************
 * Construction, moving, and Copying
*******************************************************************************/
/*
 * Move Constructor
 * Delegates data pointer movement to the parent class
 */
lsImageResource::lsImageResource(lsImageResource&& img) :
    lsResource{}
{
    this->operator =(std::move(img));
}

/******************************************************************************
 * Overloaded Operators
*******************************************************************************/
/*
 * Move operator
 */
lsImageResource& lsImageResource::operator =(lsImageResource&& img) {
    // Resolve movement for the base class members first
    unload();
    
    pData = img.pData;
    img.pData = nullptr;
    dataSize = img.dataSize;
    img.dataSize = 0;
    
    imgSize = img.imgSize;
    img.imgSize = math::vec2i{0};
    
    pixelSize = img.pixelSize;
    img.pixelSize = 0;
    
    bitsPerPixel = img.bitsPerPixel;
    img.bitsPerPixel = 0;
    
    imgFormat = img.imgFormat;
    img.imgFormat = math::vec2i{0,0};
    
    return *this;
}

/******************************************************************************
 * File handling
*******************************************************************************/
/*
 * Loading
 */
bool lsImageResource::loadFile(const char* filename) {
    LS_LOG_MSG("Attempting to load the image ", filename);
    unload();
    
    if (!filename) {
        LS_LOG_ERR("\tFailed to load an image as no filename was provided.\n");
        return false;
    }
    
    // Set FreeImage's error function
    FreeImage_SetOutputMessage(&printImageLoadError);
    
    // Determine the file type that should be loaded
    FREE_IMAGE_FORMAT fileFormat = deduceImageFormat(filename);
    
    if (fileFormat == FIF_UNKNOWN) {
        LS_LOG_ERR("\tUnable to determine the file type for ", filename, ".\n");
        return false;
    }
    
    if (FreeImage_FIFSupportsReading(fileFormat) == false) {
        LS_LOG_ERR(
            "\tSupport for the type of file used by ", filename,
            " is not currently implemented.\n"
        );
        return false;
    }
    
    // Preliminary setup passed. Attempt to load the file data
    
    // Use some predefined image flags
    const int fileFlags = getImageFlags(fileFormat);
    FIBITMAP* fileData = FreeImage_Load(fileFormat, filename, fileFlags);
    
    if (!fileData) {
        LS_LOG_ERR(
            "\tUnable to load the image ", filename,
            " due to an internal library error.\n"
        );
        return false;
    }
    
    const int dataType = getBitmapSize(fileData);
    if (dataType == 0) {
        LS_LOG_ERR('\t', filename, " contains an unsupported pixel format.\n");
        FreeImage_Unload(fileData);
        return false;
    }
    
    this->pData         = reinterpret_cast<char*>(fileData);
    this->imgSize[0]    = (int)FreeImage_GetWidth(fileData);
    this->imgSize[1]    = (int)FreeImage_GetHeight(fileData);
    this->bitsPerPixel  = (unsigned)FreeImage_GetBPP(fileData);
    this->pixelSize     = dataType;
    this->dataSize      = this->imgSize[0] * this->imgSize[1];
    this->imgFormat     = getPixelFormat(fileData, this->bitsPerPixel);
    
    LS_LOG_MSG("\tSuccessfully loaded ", filename, ".\n");
    
    return true;
}

/*
 * Unloading
 */
void lsImageResource::unload() {
    if (pData == nullptr) {
        return;
    }
    
    FreeImage_Unload(reinterpret_cast<FIBITMAP*>(pData));
    
    pData = nullptr;
    dataSize = 0;
    imgSize = math::vec2i{0};
    pixelSize = 0;
    bitsPerPixel = 0;
    imgFormat = math::vec2i{0,0};
}

