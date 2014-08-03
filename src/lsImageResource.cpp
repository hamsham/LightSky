/* 
 * File:   lsImageResource.cpp
 * Author: hammy
 * 
 * Created on February 2, 2014, 1:42 PM
 */

#include <utility> // std::move
#include <string>

#include <FreeImage.h>

#include "lsSetup.h"
#include "lsImageResource.h"

//-----------------------------------------------------------------------------
//      Utilities
//-----------------------------------------------------------------------------
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
ls_color_type_t getBitmapSize(FIBITMAP* pImg) {
    // Get the data type of the image. Convert to an internal format
    const int storageType = FreeImage_GetImageType(pImg);
    ls_color_type_t dataType = LS_DEFAULT_COLOR_TYPE;
    
    if (storageType == FIT_UNKNOWN
    ||  storageType == FIT_DOUBLE
    ||  storageType == FIT_COMPLEX
    ) {
        return LS_INVALID_COLOR_TYPE;
    }
    
    switch(storageType) {
        // n-bit char
        case FIT_BITMAP:
            LS_LOG_MSG("\tImage pixel type: BYTE");
            dataType = LS_UNSIGNED_BYTE;
            break;
            
        // 16-bit short
        case FIT_INT16:
            dataType = LS_SHORT;
            LS_LOG_MSG("\tImage pixel type: SHORT");
            break;
                
        case FIT_UINT16:
            dataType = LS_UNSIGNED_SHORT;
            LS_LOG_MSG("\tImage pixel type: UNSIGNED SHORT");
            break;
        
        // 32-bit int
        case FIT_INT32:
            dataType = LS_INT;
            LS_LOG_MSG("\tImage pixel type: INT");
            break;
                
        case FIT_UINT32:
            dataType = LS_UNSIGNED_INT;
            LS_LOG_MSG("\tImage pixel type: UNSIGNED INT");
            break;
        
        // 96-bit float
        case FIT_RGBF:
        // 128-bit float
        case FIT_RGBAF:
            dataType = LS_FLOAT;
            LS_LOG_MSG("\tImage pixel type: FLOAT");
            break;
        
        // unknown
        default:
            return LS_INVALID_COLOR_TYPE;
            LS_LOG_MSG("\tImage pixel type: INVALID");
            break;
    }
    
    return dataType;
}

void getPixelFormat(
    FIBITMAP* pImg,
    unsigned bpp,
    ls_pixel_format_t& intFmt,
    ls_pixel_layout_t& extFmt
) {
    LS_LOG_MSG("\tImage Bits Per Pixel: ", bpp);
    
    // setup some default values in case nothing below returns.
    intFmt = LS_INVALID_PIXEL_FORMAT;
    extFmt = LS_INVALID_PIXEL_LAYOUT;
    
    // Get the data type of the image. Convert to an internal format
    const FREE_IMAGE_TYPE dataType = FreeImage_GetImageType(pImg);
    
    if (dataType == FIT_BITMAP) {
        if (bpp == 8)   intFmt = LS_GRAY_8;     extFmt = LS_GRAY;
        if (bpp == 16)  intFmt = LS_RG_8;       extFmt = LS_RG;
        if (bpp == 24)  intFmt = LS_RGB_8;      extFmt = LS_RGB;
        if (bpp == 32)  intFmt = LS_RGBA_8;     extFmt = LS_RGBA;
    }
    else if (dataType == FIT_INT16) {
        if (bpp == 16)  intFmt = LS_GRAY_16I;   extFmt = LS_GRAY;
        if (bpp == 32)  intFmt = LS_RG_16I;     extFmt = LS_RG;
        if (bpp == 48)  intFmt = LS_RGB_16I;    extFmt = LS_RGB;
        if (bpp == 64)  intFmt = LS_RGBA_16I;   extFmt = LS_RGBA;
    }
    else if (dataType == FIT_UINT16) {
        if (bpp == 16)  intFmt = LS_GRAY_16U;   extFmt = LS_GRAY;
        if (bpp == 32)  intFmt = LS_RG_16U;     extFmt = LS_RG;
        if (bpp == 48)  intFmt = LS_RGB_16U;    extFmt = LS_RGB;
        if (bpp == 64)  intFmt = LS_RGBA_16U;   extFmt = LS_RGBA;
    }
    else if (dataType == FIT_INT32) {
        if (bpp == 32)  intFmt = LS_GRAY_32I;   extFmt = LS_GRAY;
        if (bpp == 64)  intFmt = LS_RG_32I;     extFmt = LS_RG;
        if (bpp == 96)  intFmt = LS_RGB_32I;    extFmt = LS_RGB;
        if (bpp == 128) intFmt = LS_RGBA_32I;   extFmt = LS_RGBA;
    }
    else if (dataType == FIT_UINT32) {
        if (bpp == 32)  intFmt = LS_GRAY_32U;   extFmt = LS_GRAY;
        if (bpp == 64)  intFmt = LS_RG_32U;     extFmt = LS_RG;
        if (bpp == 96)  intFmt = LS_RGB_32U;    extFmt = LS_RGB;
        if (bpp == 128) intFmt = LS_RGBA_32U;   extFmt = LS_RGBA;
    }
    else if (dataType == FIT_FLOAT) {
        if (bpp == 32)  intFmt = LS_GRAY_32F;   extFmt = LS_GRAY;
        if (bpp == 64)  intFmt = LS_RG_32F;     extFmt = LS_RG;
        if (bpp == 96)  intFmt = LS_RGB_32F;    extFmt = LS_RGB;
        if (bpp == 128) intFmt = LS_RGBA_32F;   extFmt = LS_RGBA;
    }
    else if (dataType == FIT_RGB16) {
        intFmt = LS_RGB_16F;
        extFmt = LS_RGB;
    }
    else if (dataType == FIT_RGBA16) {
        intFmt = LS_RGBA_16F;
        extFmt = LS_RGBA;
    }
    else if (dataType == FIT_RGBF) {
        intFmt = LS_RGB_32F;
        extFmt = LS_RGB;
    }
    else if (dataType == FIT_RGBAF) {
        intFmt = LS_RGBA_32F;
        extFmt = LS_RGBA;
    }
}

//-----------------------------------------------------------------------------
//      Construction, moving, and Copying
//-----------------------------------------------------------------------------
/*
 * Constructor
 */
lsImageResource::lsImageResource() :
    lsResource{}
{}

/*
 * Move Constructor
 */
lsImageResource::lsImageResource(lsImageResource&& img) :
    lsResource{}
{
    this->operator =(std::move(img));
}
    
/*
 * Destructor
 */
lsImageResource::~lsImageResource() {
    unload();
}

//-----------------------------------------------------------------------------
//      Overloaded Operators
//-----------------------------------------------------------------------------
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
    
    pixelType = img.pixelType;
    img.pixelType = LS_DEFAULT_COLOR_TYPE;
    
    bitsPerPixel = img.bitsPerPixel;
    img.bitsPerPixel = 0;
    
    intFormat = img.intFormat;
    img.intFormat = LS_DEFAULT_PIXEL_FORMAT;
    
    extFormat = img.extFormat;
    img.extFormat = LS_DEFAULT_PIXEL_LAYOUT;
    
    return *this;
}

//-----------------------------------------------------------------------------
//      File handling
//-----------------------------------------------------------------------------
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
    
    const ls_color_type_t dataType = getBitmapSize(fileData);
    if (dataType == LS_INVALID_COLOR_TYPE) {
        LS_LOG_ERR('\t', filename, " contains an unsupported pixel format.\n");
        FreeImage_Unload(fileData);
        return false;
    }
    
    this->pData         = reinterpret_cast<char*>(fileData);
    this->imgSize[0]    = (int)FreeImage_GetWidth(fileData);
    this->imgSize[1]    = (int)FreeImage_GetHeight(fileData);
    this->bitsPerPixel  = (unsigned)FreeImage_GetBPP(fileData);
    this->pixelType     = dataType;
    this->dataSize      = this->imgSize[0] * this->imgSize[1];
    
    getPixelFormat(fileData, this->bitsPerPixel, intFormat, extFormat);
    
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
    pixelType = LS_DEFAULT_COLOR_TYPE;
    bitsPerPixel = 0;
    intFormat = LS_DEFAULT_PIXEL_FORMAT;
    extFormat = LS_DEFAULT_PIXEL_LAYOUT;
}

/*
 * saving
 */
bool lsImageResource::saveFile(const char* filename, img_file_t format) const {
    FREE_IMAGE_FORMAT fiFormat = FIF_PNG;
    
    switch(format) {
        case img_file_t::LS_IMG_BMP:    fiFormat = FIF_BMP; break;
        case img_file_t::LS_IMG_EXR:    fiFormat = FIF_EXR; break;
        case img_file_t::LS_IMG_GIF:    fiFormat = FIF_GIF; break;
        case img_file_t::LS_IMG_HDR:    fiFormat = FIF_HDR; break;
        case img_file_t::LS_IMG_ICO:    fiFormat = FIF_ICO; break;
        case img_file_t::LS_IMG_JPG:    fiFormat = FIF_JPEG; break;
        case img_file_t::LS_IMG_J2K:    fiFormat = FIF_J2K; break;
        case img_file_t::LS_IMG_PNG:    fiFormat = FIF_PNG; break;
        case img_file_t::LS_IMG_PPM:    fiFormat = FIF_PPM; break;
        case img_file_t::LS_IMG_TGA:    fiFormat = FIF_TARGA; break;
        case img_file_t::LS_IMG_TIF:    fiFormat = FIF_TIFF; break;
        case img_file_t::LS_IMG_WBP:    fiFormat = FIF_WEBP; break;
        case img_file_t::LS_IMG_XPM:    fiFormat = FIF_XPM; break;
        default:                        fiFormat = FIF_PNG;
    }
    
    if (this->pData == nullptr || filename == nullptr) {
        return false;
    }
    
    return 0 != FreeImage_Save(fiFormat, reinterpret_cast<FIBITMAP*>(pData), filename);
}

/*
 * Get the data stored in pData
 */
void* lsImageResource::getData() const {
    return (void*) FreeImage_GetBits(reinterpret_cast<FIBITMAP*>(pData));
}

