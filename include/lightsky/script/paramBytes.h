/* 
 * File:   paramBytes.h
 * Author: hammy
 *
 * Created on December 22, 2014, 9:18 PM
 */

#ifndef __LS_SCRIPT_PARAM_BYTES_H__
#define	__LS_SCRIPT_PARAM_BYTES_H__

namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
    Byte Counting for Script Variables
-----------------------------------------------------------------------------*/
/**
 *  @brief getArgByteSize
 *  Helper function to sum the number of bytes used by a set of types.
 *
 *  @param size
 *  An unsigned integer representing the size, in bytes, of an object.
 *
 *  @return
 *  An unsigned integer, representing the size, in bytes, of an object. This
 *  can be the size of a built-in type, or user-defined structures.
 */
template <typename arg_t>
constexpr unsigned getVarByteSize(arg_t*) {
    return sizeof(arg_t);
}

template <>
constexpr unsigned getVarByteSize<void>(void*) {
    return 0;
}

/**
 *  @brief getArgByteSize
 *  Helper function to sum the number of bytes used by a set of types.
 *
 *  @param size
 *  An unsigned integer representing the size, in bytes, of an object.
 *
 *  @param sizeN
 *  A set of unsigned integers that contain the byte size of a set of objects.
 *
 *  @return
 *  An unsigned integer, representing the size, in bytes, of a set of object
 *  types. These types can be built-in, or user-defined structures.
 */
template <typename arg_t, typename... args_t>
constexpr unsigned getVarByteSize(arg_t*, args_t*...) {
    return sizeof(arg_t) + getVarByteSize<args_t...>(((args_t*)nullptr)...);
}

template <typename... args_t>
constexpr unsigned getFuncParamByteSize() {
    return getVarByteSize<args_t...>(((args_t*)nullptr)...);
}

} // end script namespace
} // end ls namespace

#endif	/* __LS_SCRIPT_PARAM_BYTES_H__ */

