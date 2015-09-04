
#ifndef __LS_MATH_MAT2_H__
#define __LS_MATH_MAT2_H__

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"
#include "lightsky/math/vec2.h"

namespace ls {
namespace math {

/**----------------------------------------------------------------------------
 *  @brief 2D Matrix Structure
 *  recommended for use with non-integral types
 *
 *  @note
 *  Matrix is Row-Major
 *  Orientation is as follows:
 *      0[0-1] = XX  XY
 *      1[0-1] = YX  YY
-----------------------------------------------------------------------------*/
template <typename num_t>
struct mat2_t {
    // data
    vec2_t<num_t> m[2];

    // Main Constructor
    constexpr mat2_t(
        num_t inXX, num_t inXY,
        num_t inYX, num_t inYY
    );

    // Delegated constructors
    constexpr mat2_t();
    constexpr mat2_t(num_t);
    constexpr mat2_t(const mat2_t<num_t>&);
    constexpr mat2_t(mat2_t<num_t>&&);
    constexpr mat2_t(
        const vec2_t<num_t>& x,
        const vec2_t<num_t>& y
    );

    ~mat2_t() = default;

    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator mat2_t<other_t>() const;

    // Subscripting
    inline const vec2_t<num_t>& operator[] (int i) const;
    inline vec2_t<num_t>&       operator[] (int i);

    //mat-mat operators
    mat2_t&         operator    ++      (); //prefix operators
    mat2_t&         operator    --      ();
    mat2_t          operator    ++      (int); //postfix operators
    mat2_t          operator    --      (int);
    mat2_t          operator    +       (const mat2_t<num_t>& input) const;
    mat2_t          operator    -       (const mat2_t<num_t>& input) const;
    mat2_t          operator    -       () const;
    mat2_t          operator    *       (const mat2_t<num_t>& input) const;
    mat2_t&         operator    =       (const mat2_t<num_t>& input);
    mat2_t&         operator    =       (mat2_t<num_t>&& input);
    mat2_t&         operator    +=      (const mat2_t<num_t>& input);
    mat2_t&         operator    -=      (const mat2_t<num_t>& input);
    mat2_t&         operator    *=      (const mat2_t<num_t>& input);
    bool            operator    ==      (const mat2_t<num_t>& input) const;
    bool            operator    !=      (const mat2_t<num_t>& input) const;

    //mat-vector operators
    mat2_t          operator    +       (const vec2_t<num_t>&) const;
    mat2_t          operator    -       (const vec2_t<num_t>&) const;
    vec2_t<num_t>   operator    *       (const vec2_t<num_t>&) const;
    mat2_t&         operator    =       (const vec2_t<num_t>&);
    mat2_t&         operator    +=      (const vec2_t<num_t>&);
    mat2_t&         operator    -=      (const vec2_t<num_t>&);

    //mat-scalar operators
    mat2_t          operator    +       (num_t) const;
    mat2_t          operator    -       (num_t) const;
    mat2_t          operator    *       (num_t) const;
    mat2_t          operator    /       (num_t) const;
    mat2_t&         operator    =       (num_t);
    mat2_t&         operator    +=      (num_t);
    mat2_t&         operator    -=      (num_t);
    mat2_t&         operator    *=      (num_t);
    mat2_t&         operator    /=      (num_t);
};

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> inline
mat2_t<num_t> operator + (num_t n, const mat2_t<num_t>& m);

template <typename num_t> inline
mat2_t<num_t> operator - (num_t n, const mat2_t<num_t>& m);

template <typename num_t> inline
mat2_t<num_t> operator * (num_t n, const mat2_t<num_t>& m);

/*-------------------------------------
    2x2 Matrix Specializations
-------------------------------------*/
LS_DECLARE_STRUCT_TYPE(mat2f,    mat2_t, float);
LS_DECLARE_STRUCT_TYPE(mat2d,    mat2_t, double);
LS_DECLARE_STRUCT_TYPE(mat2i,    mat2_t, int);
LS_DECLARE_STRUCT_TYPE(mat2ui,   mat2_t, unsigned);
LS_DECLARE_STRUCT_TYPE(mat2x,    mat2_t, medp_t);
LS_DECLARE_STRUCT_TYPE(mat2,     mat2_t, LS_FLOAT);

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/mat2_impl.h"

#endif /*__LS_MATH_MAT2_H__*/
