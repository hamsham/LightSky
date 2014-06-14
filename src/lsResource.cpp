/* 
 * File:   resource.cpp
 * Author: hammy
 * 
 * Created on February 1, 2014, 11:09 PM
 */

#include <cstdlib> // std::wcstombs
#include <cstring> // std::memset, std::wcslen
#include "lsSetup.h"
#include "lsResource.h"

/******************************************************************************
 * Utilities
*******************************************************************************/
/*
 * Input a UTF-8 string and return a dynamically allocated multi-byte string
 */
char* convertWtoMb(const wchar_t* wstr) {
    // get the size difference between the two data types
    unsigned sizeDifference = sizeof(wchar_t) / sizeof(char);
    
    LS_LOG_MSG(
        "UTF-8 string provided. Attempting to convert the UTF-8 string ",
        wstr, " to a multi-byte string."
    );
    
    // convert the wide string to a multi-byte char string
    std::size_t stringSize = std::wcslen(wstr)*sizeDifference;
    char* str = new(std::nothrow) char[stringSize];
    
    if (!str) {
        LS_LOG_ERR(
            "Unable to allocate ", stringSize,
            " bytes to convert the UTF-8 string ", wstr,
            " to a multi-byte string.\n"
        );
        return nullptr;
    }
    else {
        // 0-initialize the string
        std::memset(str, 0, stringSize);
    }
    
    // convert the wide char to multi-byte
    std::size_t err = std::wcstombs(str, wstr, stringSize);
    
    // make sure the conversion worked
    if (err == ((std::size_t)-1)) {
        LS_LOG_ERR(
            "Unable to convert the UTF-8 string ",
            wstr, " to a multi-byte string.\n"
        );
        delete [] str;
        return nullptr;
    }
    
    LS_LOG_MSG(
        "Successfully converted the UTF-8 string ", wstr,
        " to a multi-byte string: ", str, ".\n"
    );
    
    return str;
}

/******************************************************************************
 * Resource Methods
*******************************************************************************/
/*
 * Destructor
 */
lsResource::~lsResource() {
}

/*
 * Open a file with UTF-8
 */
bool lsResource::loadFile(const wchar_t* filename) {
    unsigned sizeDifference = sizeof(wchar_t) / sizeof(char);
    
    // check if the compiler makes char and wchar_t the same size
    if (sizeDifference <= 1) {
        return loadFile((char*)filename);
    }
    
    // Get a dynamically allocated string, converted from UTF-8
    char* mbFilename = convertWtoMb(filename);
    if (mbFilename == nullptr) {
        return false;
    }
    
    // attempt to load the file
    bool ret = loadFile(mbFilename);
    delete [] mbFilename;
    return ret;
}

/*
 * Save with an UTF-8 filename
 */
bool lsResource::saveFile(const wchar_t* filename) const {
    unsigned sizeDifference = sizeof(wchar_t) / sizeof(char);
    
    // check if the compiler makes char and wchar_t the same size
    if (sizeDifference <= 1) {
        return saveFile((char*)filename);
    }
    
    // Get a dynamically allocated string, converted from UTF-8
    char* mbFilename = convertWtoMb(filename);
    if (mbFilename == nullptr) {
        return false;
    }
    
    // attempt to save the file
    bool ret = saveFile(mbFilename);
    delete [] mbFilename;
    return ret;
}
