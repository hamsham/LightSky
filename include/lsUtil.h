/* 
 * File:   lsUtil.h
 * Author: miles
 *
 * Created on May 23, 2014, 7:10 PM
 */

#ifndef __LS_UTIL_H__
#define	__LS_UTIL_H__

#include <string>
#include <sstream>

/**
 * LightSky Utility functions
 */
namespace lsUtil {

/**
 * toString
 * MinGW Doesn't currently have std::to_string()
 * 
 * @param T
 * A generic type that can be printed to an std::ostream
 * 
 * @return std::string
 * A string-representation of the input parameter
 */
template <typename T>
std::string toString(const T& data) {
    std::ostringstream oss;
    oss << data;
    return oss.str();
}

/**
 * Convert a Wide String to a multibyte-character string
 */
std::string convertWtoMb(const std::wstring& wstr);

}

#endif	/* __LS_UTIL_H__ */

