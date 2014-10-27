
#ifndef __LS_MATH_VEC4_H__
#define __LS_MATH_VEC4_H__

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

/* 4x4 Matrix forward declaration */
template <typename num_t>
struct mat4_t;

/**----------------------------------------------------------------------------
 *  @brief 4D Vector Structure
 *  
 *  Recommended for use with non-integral types
 *  
 *  @note
 *  Indexing is as follows:
 *      0 = X
 *      1 = Y
 *      2 = Z
 *      3 = W
-----------------------------------------------------------------------------*/
template <typename num_t>
struct vec4_t {
    // data
    num_t v[4];
    
    // Main Constructor
    constexpr vec4_t(num_t inX, num_t inY, num_t inZ, num_t inW);
    
    // Delegated Constructors
    constexpr vec4_t();
    constexpr vec4_t(num_t n);
    constexpr vec4_t(const vec4_t<num_t>& input);
    constexpr vec4_t(vec4_t<num_t>&& input);
    
    ~vec4_t() = default;
    
    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator vec4_t<other_t>() const;
    
    const num_t*    operator    &   () const;
    inline num_t*   operator    &   ();
    
    // Subscripting Operators
    constexpr num_t operator    []  (int i) const;
    inline num_t&   operator    []  (int i);

    // vector-vector operators
    vec4_t          operator    +   (const vec4_t<num_t>&) const;
    vec4_t          operator    -   (const vec4_t<num_t>&) const;
    vec4_t          operator    -   () const;
    vec4_t          operator    *   (const vec4_t<num_t>&) const;
    vec4_t          operator    /   (const vec4_t<num_t>&) const;
    vec4_t&         operator    =   (const vec4_t<num_t>&);
    vec4_t&         operator    =   (vec4_t<num_t>&&);
    vec4_t&         operator    +=  (const vec4_t<num_t>&);
    vec4_t&         operator    -=  (const vec4_t<num_t>&);
    vec4_t&         operator    *=  (const vec4_t<num_t>&);
    vec4_t&         operator    /=  (const vec4_t<num_t>&);
    vec4_t&         operator    ++  (); //prefix operators
    vec4_t&         operator    --  ();
    vec4_t          operator    ++  (int); //postfix operators
    vec4_t          operator    --  (int);
    bool            operator    ==  (const vec4_t<num_t>& compare) const; //comparisons
    bool            operator    !=  (const vec4_t<num_t>& compare) const;
    bool            operator    <   (const vec4_t<num_t>& compare) const;
    bool            operator    >   (const vec4_t<num_t>& compare) const;
    bool            operator    <=  (const vec4_t<num_t>& compare) const;
    bool            operator    >=  (const vec4_t<num_t>& compare) const;

    // vector-matrix operators (implementation in the matrix4 header)
    mat4_t<num_t>   operator    +   (const mat4_t<num_t>&) const;
    mat4_t<num_t>   operator    -   (const mat4_t<num_t>&) const;
    vec4_t<num_t>   operator    *   (const mat4_t<num_t>&) const;
    vec4_t&         operator    *=  (const mat4_t<num_t>&);

    // vector-scalar operators
    vec4_t          operator    =   (num_t);
    vec4_t          operator    +   (num_t) const;
    vec4_t          operator    -   (num_t) const;
    vec4_t          operator    *   (num_t) const;
    vec4_t          operator    /   (num_t) const;
    vec4_t&         operator    +=  (num_t);
    vec4_t&         operator    -=  (num_t);
    vec4_t&         operator    *=  (num_t);
    vec4_t&         operator    /=  (num_t);
};

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
template <typename num_t> inline
vec4_t<num_t> operator + (num_t n, const vec4_t<num_t>& v);

template <typename num_t> inline
vec4_t<num_t> operator - (num_t n, const vec4_t<num_t>& v);

template <typename num_t> inline
vec4_t<num_t> operator * (num_t n, const vec4_t<num_t>& v);

/*-------------------------------------
    4D Vector Specializations
-------------------------------------*/
LS_DECLARE_CLASS_TYPE(vec4f,    vec4_t, float);
LS_DECLARE_CLASS_TYPE(vec4d,    vec4_t, double);
LS_DECLARE_CLASS_TYPE(vec4i,    vec4_t, int);
LS_DECLARE_CLASS_TYPE(vec4ui,   vec4_t, unsigned);
LS_DECLARE_CLASS_TYPE(vec4x,    vec4_t, medp_t);
LS_DECLARE_CLASS_TYPE(vec4,     vec4_t, LS_FLOAT);

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/vec4_impl.h"

#endif /* __LS_MATH_VEC4_H__*/
