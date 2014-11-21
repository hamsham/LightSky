/* 
 * File:   setup/macros.h
 * Author: Miles Lacey
 *
 * This file contains macros and definitions used throughout LightSky
 */

#ifndef __LS_SETUP_MACROS_H__
#define __LS_SETUP_MACROS_H__

#include <type_traits>

/*
 * Preprocessor Stringify
 */
#ifndef LS_STRINGIFY
    #define LS_STRINGIFY(x) #x
#endif /* LS_STRINGIFY */

/*
 * Maxumum value
 */
#ifndef LS_MAX
    #define LS_MAX(x, y) ((x > y) ? x : y)
#endif

/*
 * Minimum Value
 */
#ifndef LS_MIN
    #define LS_MIN(x, y) ((x < y) ? x : y)
#endif

/*
 * Get the number of elements contained in a stack-allocated array.
 */
#ifndef LS_ARRAY_SIZE
	#define LS_ARRAY_SIZE( a ) ( sizeof( a ) / sizeof( a[0] ) )
#endif

/*
 * Class Template Declaration
 *
 * This macro declares a template class as "extern," providing the ability to
 * use non-instantiated templated classes. It also provides a typedef in order
 * to give each template type an alias.
 */
#ifndef LS_DECLARE_CLASS_TYPE
    #define LS_DECLARE_CLASS_TYPE(nickName, name, ...)\
        typedef name<__VA_ARGS__> nickName; \
        extern template class name<__VA_ARGS__>
#endif

/*
 * Class Template Definitions
 * 
 * This macro is used to explicitly instantiate templated classes.
 */
#ifndef LS_DEFINE_CLASS_TYPE
    #define LS_DEFINE_CLASS_TYPE(name, ...) template class name<__VA_ARGS__>
#endif

/*
 * The LS_ENUM_VAL macro will extract the numerical value of any type declared
 * using "enum class." A compiler error will be thrown if the input argument is
 * not an enumeration.
 */
#ifndef LS_ENUM_VAL
    #define LS_ENUM_VAL( x ) static_cast<std::underlying_type<decltype(x)>::type>(x)
#endif

#endif /* __LS_SETUP_MACROS_H__ */
