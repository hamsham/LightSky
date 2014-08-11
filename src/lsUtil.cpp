/* 
 * File:   lsUtil.cpp
 * Author: miles
 * 
 * Created on May 23, 2014, 7:10 PM
 */

#include <cstdlib> // std::wcstombs
#include <cstring> // std::memset, std::wcslen

#include "lsSetup.h"
#include "lsUtil.h"

//-----------------------------------------------------------------------------
//      Utilities
//-----------------------------------------------------------------------------
/*
 * Input a UTF-8 string and return a dynamically allocated multi-byte string
 */
std::string lsUtil::convertWtoMb(const std::wstring& wstr) {
    // return value
    std::string ret = "";
    
    // get the size difference between the two data types
    unsigned sizeDifference = sizeof(wchar_t) / sizeof(char);
    
    LS_LOG_MSG(
        "UTF-8 string provided. Attempting to convert the UTF-8 string ",
        wstr.c_str(), " to a multi-byte string."
    );
    
    // convert the wide string to a multi-byte char string
    std::size_t maxBytes = wstr.size()*sizeDifference;
    
    // Allocate a new character array
    char* const str = new(std::nothrow) char[maxBytes];
    
    if (!str) {
        LS_LOG_ERR(
            "Unable to allocate ", maxBytes,
            " bytes to convert the UTF-8 string ", wstr.c_str(),
            " to a multi-byte string.\n"
        );
        return ret;
    }
    else {
        // 0-initialize the string, just in case
        std::memset(str, 0, maxBytes);
    }
    
    // convert the wide char to multi-byte
    std::size_t err = std::wcstombs(str, wstr.c_str(), maxBytes);
    
    // make sure the conversion worked
    if (err == ((std::size_t)-1)) {
        LS_LOG_ERR(
            "Unable to convert the UTF-8 string ",
            wstr.c_str(), " to a multi-byte string.\n"
        );
    }
    else {
        LS_LOG_MSG(
            "Successfully converted the UTF-8 string ", wstr.c_str(),
            " to a multi-byte string: ", str, ".\n"
        );
        
        // copy the new multi-byte string into the return value.
        ret.assign(str, maxBytes);
    }
    
    delete [] str;
    
    return ret;
}
