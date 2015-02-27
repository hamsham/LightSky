
#ifndef __LS_MATH_MAT4_H__
#define __LS_MATH_MAT4_H__

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"
#include "lightsky/math/vec4.h"
#include "lightsky/math/mat3.h"

namespace ls {
namespace math {

/**----------------------------------------------------------------------------
 *  @brief 4D Matrix Structure
 *  recommended for use with non-integral types
 *
 *  @note
 *  Matrix is Row-Major
 *  Orientation is as follows:
 *      0[0-3] = XX  XY  XZ  XW
 *      1[0-3] = YX  YY  YZ  YW
 *      2[0-3] = ZX  ZY  ZZ  ZW
 *      3[0-3] = WX  WY  WZ  WW
-----------------------------------------------------------------------------*/
template <typename num_t>
struct mat4_t {
    // data
    vec4_t<num_t> m[4];

    // Main Constructor
    constexpr mat4_t(
        num_t inXX, num_t inXY, num_t inXZ, num_t inXW,
        num_t inYX, num_t inYY, num_t inYZ, num_t inYW,
        num_t inZX, num_t inZY, num_t inZZ, num_t inZW,
        num_t inWX, num_t inWY, num_t inWZ, num_t inWW
    );

    // Delegated constructors
    constexpr mat4_t();
    constexpr mat4_t(num_t);
    constexpr mat4_t(const mat3_t<num_t>&);
    constexpr mat4_t(const mat4_t<num_t>&);
    constexpr mat4_t(mat3_t<num_t>&&);
    constexpr mat4_t(mat4_t<num_t>&&);
    constexpr mat4_t(
        const vec4_t<num_t>& x,
        const vec4_t<num_t>& y,
        const vec4_t<num_t>& z,
        const vec4_t<num_t>& w
    );

    ~mat4_t() = default;

    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator mat4_t<other_t>() const;

    // Subscripting Operators
    inline const vec4_t<num_t>& operator[] (int i) const;
    inline vec4_t<num_t>&       operator[] (int i);

    //matrix-matrix operators
    mat4_t&         operator    ++      (); //prefix operators
    mat4_t&         operator    --      ();
    mat4_t          operator    ++      (int); //postfix operators
    mat4_t          operator    --      (int);
    mat4_t          operator    +       (const mat4_t<num_t>& input) const;
    mat4_t          operator    -       (const mat4_t<num_t>& input) const;
    mat4_t          operator    -       () const;
    mat4_t          operator    *       (const mat4_t<num_t>& input) const;
    mat4_t&         operator    =       (const mat4_t<num_t>& input);
    mat4_t&         operator    =       (mat4_t<num_t>&& input);
    mat4_t&         operator    +=      (const mat4_t<num_t>& input);
    mat4_t&         operator    -=      (const mat4_t<num_t>& input);
    mat4_t&         operator    *=      (const mat4_t<num_t>& input);
    bool            operator    ==      (const mat4_t<num_t>& input) const;
    bool            operator    !=      (const mat4_t<num_t>& input) const;

    //matrix-vector operators
    mat4_t          operator    +       (const vec4_t<num_t>&) const;
    mat4_t          operator    -       (const vec4_t<num_t>&) const;
    vec4_t<num_t>   operator    *       (const vec4_t<num_t>&) const;
    mat4_t&         operator    =       (const vec4_t<num_t>&);
    mat4_t&         operator    +=      (const vec4_t<num_t>&);
    mat4_t&         operator    -=      (const vec4_t<num_t>&);

    //matrix-scalar operators
    mat4_t          operator    +       (num_t) const;
    mat4_t          operator    -       (num_t) const;
    mat4_t          operator    *       (num_t) const;
    mat4_t          operator    /       (num_t) const;
    mat4_t&         operator    =       (num_t);
    mat4_t&         operator    +=      (num_t);
    mat4_t&         operator    -=      (num_t);
    mat4_t&         operator    *=      (num_t);
    mat4_t&         operator    /=      (num_t);
};

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> inline
mat4_t<num_t> operator + (num_t n, const mat4_t<num_t>& m);

template <typename num_t> inline
mat4_t<num_t> operator - (num_t n, const mat4_t<num_t>& m);

template <typename num_t> inline
mat4_t<num_t> operator * (num_t n, const mat4_t<num_t>& m);

/*-------------------------------------
    4x4 Matrix Specializations
-------------------------------------*/
LS_DECLARE_STRUCT_TYPE(mat4f,    mat4_t, float);
LS_DECLARE_STRUCT_TYPE(mat4d,    mat4_t, double);
LS_DECLARE_STRUCT_TYPE(mat4i,    mat4_t, int);
LS_DECLARE_STRUCT_TYPE(mat4ui,   mat4_t, unsigned);
LS_DECLARE_STRUCT_TYPE(mat4x,    mat4_t, medp_t);
LS_DECLARE_STRUCT_TYPE(mat4,     mat4_t, LS_FLOAT);

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/mat4_impl.h"

#endif /*__LS_MATH_MAT4_H__*/
