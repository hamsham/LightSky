/* 
 * File:   imageResource.cpp
 * Author: hammy
 * 
 * Created on February 2, 2014, 1:42 PM
 */

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
void printImageLoadError(FREE_IMAGE_FORMAT fif, const char* msg) {
	LS_LOG_ERR(
        "\tAn image file error has occurred:",
        "\n\tFormat: ", FreeImage_GetFormatFromFIF(fif),
        "\n\t", msg, "."
    );
}

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
 * Get the bits per pixel of an image, 0, 1, 4, 8, 16, 24, or 32
 */
inline unsigned getBitsPerPixel(FIBITMAP* pImg) {
    int bpp = FreeImage_GetBPP(pImg);
    return bpp != -1 ? (unsigned)bpp : 0;
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
            dataType = GL_BYTE;
            break;
            
        // 16-bit short
        case FIT_INT16:
            dataType = GL_SHORT;
            LS_LOG_MSG("\tImage pixel type: UNSIGNED SHORT");
                break;
                
        case FIT_UINT16:
            dataType = GL_UNSIGNED_SHORT;
            LS_LOG_MSG("\tImage pixel type: SHORT");
            break;
        
        // 32-bit int
        case FIT_INT32:
            dataType = GL_INT;
            LS_LOG_MSG("\tImage pixel type: UNSIGNED INT");
            break;
                
        case FIT_UINT32:
            dataType = GL_INT;
            LS_LOG_MSG("\tImage pixel type: INT");
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
    
    LS_LOG_MSG("\tSuccessfully loaded ", filename, ".\n");
    
    this->pData = reinterpret_cast<char*>(fileData);
    this->imgSize[0] = (int)FreeImage_GetWidth(fileData);
    this->imgSize[1] = (int)FreeImage_GetHeight(fileData);
    this->pixelSize = dataType;
    this->dataSize = this->imgSize[0] * this->imgSize[1];
    this->bitsPerPixel = getBitsPerPixel(fileData);
    
    return true;
}

/*
 * saving
 */
bool lsImageResource::saveFile(const char* filename) const {
    if (this->pData == nullptr || filename == nullptr) {
        return false;
    }
    
    std::string outFile = filename;
    outFile.append(".png");
    
    return FreeImage_Save(FIF_PNG, reinterpret_cast<FIBITMAP*>(pData), outFile.c_str());
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
}

/*
 * Get the data stored in pData
 */
void* lsImageResource::getData() const {
    return (char*) FreeImage_GetBits(reinterpret_cast<FIBITMAP*>(pData));
}
