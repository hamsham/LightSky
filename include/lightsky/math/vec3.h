
#ifndef __LS_MATH_VEC3_H__
#define __LS_MATH_VEC3_H__

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

/* 3x3 Matrix forward declaration */
template <typename num_t>
struct mat3_t;

/**----------------------------------------------------------------------------
 *  @brief 3D Vector Structure
 *  
 *  Recommended for use with non-integral types
 *
 *  @note
 *  Indexing is as follows:
 *      0 = X
 *      1 = Y
 *      2 = Z
-----------------------------------------------------------------------------*/
template <typename num_t>
struct vec3_t {
    // data
    num_t v[3];
    
    // Main Constructor
    constexpr vec3_t(num_t inX, num_t inY, num_t inZ);
    
    // Delegated Constructors
    constexpr vec3_t();
    constexpr vec3_t(num_t n);
    constexpr vec3_t(const vec3_t<num_t>& input);
    constexpr vec3_t(vec3_t<num_t>&& input);
    
    ~vec3_t() = default;
    
    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator vec3_t<other_t>() const;
    
    const num_t*    operator    &   () const;
    inline num_t*   operator    &   ();
    
    // Subscripting Operators
    constexpr num_t operator    []  (int i) const;
    inline num_t&   operator    []  (int i);

    //vector-vector operators
    vec3_t          operator    +   (const vec3_t<num_t>&) const;
    vec3_t          operator    -   (const vec3_t<num_t>&) const;
    vec3_t          operator    -   () const;
    vec3_t          operator    *   (const vec3_t<num_t>&) const;
    vec3_t          operator    /   (const vec3_t<num_t>&) const;
    vec3_t&         operator    =   (const vec3_t<num_t>&);
    vec3_t&         operator    =   (vec3_t<num_t>&&);
    vec3_t&         operator    +=  (const vec3_t<num_t>&);
    vec3_t&         operator    -=  (const vec3_t<num_t>&);
    vec3_t&         operator    *=  (const vec3_t<num_t>&);
    vec3_t&         operator    /=  (const vec3_t<num_t>&);
    vec3_t&         operator    ++  (); //prefix operators
    vec3_t&         operator    --  ();
    vec3_t          operator    ++  (int); //postfix operators
    vec3_t          operator    --  (int);
    bool            operator    ==  (const vec3_t<num_t>& compare) const; //comparisons
    bool            operator    !=  (const vec3_t<num_t>& compare) const;
    bool            operator    <   (const vec3_t<num_t>& compare) const;
    bool            operator    >   (const vec3_t<num_t>& compare) const;
    bool            operator    <=  (const vec3_t<num_t>& compare) const;
    bool            operator    >=  (const vec3_t<num_t>& compare) const;

    //vector-matrix operators (implementation in the matrix3 header)
    mat3_t<num_t>   operator     +   (const mat3_t<num_t>&) const;
    mat3_t<num_t>   operator     -   (const mat3_t<num_t>&) const;
    vec3_t<num_t>   operator     *   (const mat3_t<num_t>&) const;
    vec3_t&         operator     *=  (const mat3_t<num_t>&);

    //vector-scalar operators
    vec3_t          operator    =   (num_t);
    vec3_t          operator    +   (num_t) const;
    vec3_t          operator    -   (num_t) const;
    vec3_t          operator    *   (num_t) const;
    vec3_t          operator    /   (num_t) const;
    vec3_t&         operator    +=  (num_t);
    vec3_t&         operator    -=  (num_t);
    vec3_t&         operator    *=  (num_t);
    vec3_t&         operator    /=  (num_t);
};

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
template <typename num_t> inline
vec3_t<num_t> operator + (num_t n, const vec3_t<num_t>& v);

template <typename num_t> inline
vec3_t<num_t> operator - (num_t n, const vec3_t<num_t>& v);

template <typename num_t> inline
vec3_t<num_t> operator * (num_t n, const vec3_t<num_t>& v);

/*-------------------------------------
    3D Vector Specializations
-------------------------------------*/
LS_DECLARE_STRUCT_TYPE(vec3f,    vec3_t, float);
LS_DECLARE_STRUCT_TYPE(vec3d,    vec3_t, double);
LS_DECLARE_STRUCT_TYPE(vec3i,    vec3_t, int);
LS_DECLARE_STRUCT_TYPE(vec3ui,   vec3_t, unsigned);
LS_DECLARE_STRUCT_TYPE(vec3x,    vec3_t, medp_t);
LS_DECLARE_STRUCT_TYPE(vec3,     vec3_t, LS_FLOAT);

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/vec3_impl.h"

#endif /* __LS_MATH_VEC3_H__ */
