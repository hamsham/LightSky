
#ifndef __LS_MATH_MAT3_H__
#define __LS_MATH_MAT3_H__

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"
#include "lightsky/math/vec3.h"

namespace ls {
namespace math {

/**----------------------------------------------------------------------------
 *  @brief 3D Matrix Structure
 *  recommended for use with non-integral types
 *
 *  @note
 *  Matrix is Row-Major
 *  Orientation is as follows:
 *      0[0-2] = XX  XY  XZ
 *      1[0-2] = YX  YY  YZ
 *      2[0-2] = ZX  ZY  ZZ
-----------------------------------------------------------------------------*/
template <typename num_t>
struct mat3_t {
    // data
    vec3_t<num_t> m[3];

    // Main Constructor
    constexpr mat3_t(
        num_t inXX, num_t inXY, num_t inXZ,
        num_t inYX, num_t inYY, num_t inYZ,
        num_t inZX, num_t inZY, num_t inZZ
    );

    // Delegated Constructors
    constexpr mat3_t();
    constexpr mat3_t(num_t);
    constexpr mat3_t(const mat3_t<num_t>&);
    constexpr mat3_t(mat3_t<num_t>&&);
    constexpr mat3_t(
        const vec3_t<num_t>& x,
        const vec3_t<num_t>& y,
        const vec3_t<num_t>& z
    );

    ~mat3_t() = default;

    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator mat3_t<other_t>() const;

    //Subscripting operators
    inline const vec3_t<num_t>& operator[] (int i) const;
    inline vec3_t<num_t>&       operator[] (int i);

    //matrix-matrix operators
    mat3_t&         operator    ++      (); //prefix operators
    mat3_t&         operator    --      ();
    mat3_t          operator    ++      (int); //postfix operators
    mat3_t          operator    --      (int);
    mat3_t          operator    +       (const mat3_t<num_t>& input) const;
    mat3_t          operator    -       (const mat3_t<num_t>& input) const;
    mat3_t          operator    -       () const;
    mat3_t          operator    *       (const mat3_t<num_t>& input) const;
    mat3_t&         operator    =       (const mat3_t<num_t>& input);
    mat3_t&         operator    =       (mat3_t<num_t>&& input);
    mat3_t&         operator    +=      (const mat3_t<num_t>& input);
    mat3_t&         operator    -=      (const mat3_t<num_t>& input);
    mat3_t&         operator    *=      (const mat3_t<num_t>& input);
    bool            operator    ==      (const mat3_t<num_t>& input) const;
    bool            operator    !=      (const mat3_t<num_t>& input) const;

    //matrix-vector operators
    mat3_t          operator    +       (const vec3_t<num_t>&) const;
    mat3_t          operator    -       (const vec3_t<num_t>&) const;
    vec3_t<num_t>   operator    *       (const vec3_t<num_t>&) const;
    mat3_t&         operator    =       (const vec3_t<num_t>&);
    mat3_t&         operator    +=      (const vec3_t<num_t>&);
    mat3_t&         operator    -=      (const vec3_t<num_t>&);

    //matrix-scalar operators
    mat3_t          operator    +       (num_t) const;
    mat3_t          operator    -       (num_t) const;
    mat3_t          operator    *       (num_t) const;
    mat3_t          operator    /       (num_t) const;
    mat3_t&         operator    =       (num_t);
    mat3_t&         operator    +=      (num_t);
    mat3_t&         operator    -=      (num_t);
    mat3_t&         operator    *=      (num_t);
    mat3_t&         operator    /=      (num_t);
};

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> inline
mat3_t<num_t> operator + (num_t n, const mat3_t<num_t>& m);

template <typename num_t> inline
mat3_t<num_t> operator - (num_t n, const mat3_t<num_t>& m);

template <typename num_t> inline
mat3_t<num_t> operator * (num_t n, const mat3_t<num_t>& m);

/*-------------------------------------
    3x3 Matrix Specializations
-------------------------------------*/
LS_DECLARE_STRUCT_TYPE(mat3f,    mat3_t, float);
LS_DECLARE_STRUCT_TYPE(mat3d,    mat3_t, double);
LS_DECLARE_STRUCT_TYPE(mat3i,    mat3_t, int);
LS_DECLARE_STRUCT_TYPE(mat3ui,   mat3_t, unsigned);
LS_DECLARE_STRUCT_TYPE(mat3x,    mat3_t, medp_t);
LS_DECLARE_STRUCT_TYPE(mat3,     mat3_t, LS_FLOAT);

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/mat3_impl.h"

#endif /*__LS_MATH_MAT3_H__*/
