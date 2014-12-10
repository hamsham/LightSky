
#ifndef __LS_MATH_VEC2_H__
#define __LS_MATH_VEC2_H__

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

/* 2x2 Matrix forward declaration */
template <typename num_t>
struct mat2_t;

/**----------------------------------------------------------------------------
 *  @brief 2D Vector Structure
 *  
 *  Recommended for use with non-integral types
 *
 *  @note
 *  Indexing is as follows:
 *      0 = X
 *      1 = Y
-----------------------------------------------------------------------------*/
template <typename num_t>
struct vec2_t {
    // data
    num_t v[2];
    
    // Main Constructor
    constexpr vec2_t(num_t inX, num_t inY);
    
    // Delegated Constructors
    constexpr vec2_t();
    constexpr vec2_t(num_t n);
    constexpr vec2_t(const vec2_t<num_t>& input);
    constexpr vec2_t(vec2_t<num_t>&& input);
    
    ~vec2_t() = default;
    
    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator vec2_t<other_t>() const;
    
    const num_t*    operator    &   () const;
    inline num_t*   operator    &   ();
    
    // Subscripting Operators
    constexpr num_t operator    []  (int i) const;
    inline num_t&   operator    []  (int i);
    
    //vector-vector operators
    vec2_t          operator    +   (const vec2_t<num_t>&) const;
    vec2_t          operator    -   (const vec2_t<num_t>&) const;
    vec2_t          operator    -   () const;
    vec2_t          operator    *   (const vec2_t<num_t>&) const;
    vec2_t          operator    /   (const vec2_t<num_t>&) const;
    vec2_t&         operator    =   (const vec2_t<num_t>&);
    vec2_t&         operator    =   (vec2_t<num_t>&&);
    vec2_t&         operator    +=  (const vec2_t<num_t>&);
    vec2_t&         operator    -=  (const vec2_t<num_t>&);
    vec2_t&         operator    *=  (const vec2_t<num_t>&);
    vec2_t&         operator    /=  (const vec2_t<num_t>&);
    vec2_t&         operator    ++  (); //prefix operators
    vec2_t&         operator    --  ();
    vec2_t          operator    ++  (int); //postfix operators
    vec2_t          operator    --  (int);
    bool            operator    ==  (const vec2_t<num_t>& compare) const; //comparisons
    bool            operator    !=  (const vec2_t<num_t>& compare) const;
    bool            operator    <   (const vec2_t<num_t>& compare) const;
    bool            operator    >   (const vec2_t<num_t>& compare) const;
    bool            operator    <=  (const vec2_t<num_t>& compare) const;
    bool            operator    >=  (const vec2_t<num_t>& compare) const;

    //vector-matrix operators (implementation in the matrix2 header)
    mat2_t<num_t>   operator    +   (const mat2_t<num_t>&) const;
    mat2_t<num_t>   operator    -   (const mat2_t<num_t>&) const;
    vec2_t<num_t>   operator    *   (const mat2_t<num_t>&) const;
    vec2_t&         operator    *=  (const mat2_t<num_t>&);

    //vector-scalar operators
    vec2_t          operator    =   (num_t);
    vec2_t          operator    +   (num_t) const;
    vec2_t          operator    -   (num_t) const;
    vec2_t          operator    *   (num_t) const;
    vec2_t          operator    /   (num_t) const;
    vec2_t&         operator    +=  (num_t);
    vec2_t&         operator    -=  (num_t);
    vec2_t&         operator    *=  (num_t);
    vec2_t&         operator    /=  (num_t);
};

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> inline
vec2_t<num_t> operator + (num_t n, const vec2_t<num_t>& v);

template <typename num_t> inline
vec2_t<num_t> operator - (num_t n, const vec2_t<num_t>& v);

template <typename num_t> inline
vec2_t<num_t> operator * (num_t n, const vec2_t<num_t>& v);

/*-------------------------------------
    2D Vector Specializations
-------------------------------------*/
LS_DECLARE_STRUCT_TYPE(vec2f,    vec2_t, float);
LS_DECLARE_STRUCT_TYPE(vec2d,    vec2_t, double);
LS_DECLARE_STRUCT_TYPE(vec2i,    vec2_t, int);
LS_DECLARE_STRUCT_TYPE(vec2ui,   vec2_t, unsigned);
LS_DECLARE_STRUCT_TYPE(vec2x,    vec2_t, medp_t);
LS_DECLARE_STRUCT_TYPE(vec2,     vec2_t, LS_FLOAT);

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/vec2_impl.h"

#endif /* __LS_MATH_VEC2_H__ */
