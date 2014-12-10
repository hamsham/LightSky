
#ifndef __LS_MATH_QUAT_H__
#define __LS_MATH_QUAT_H__

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

/**----------------------------------------------------------------------------
 *  @brief Quaternion Structure
 *  
 *  Recommended for use with non-integral types
 *  
 *  @note
 *  Indexing is as follows:
 *      0 = X
 *      1 = Y
 *      2 = Z
 *      3 = W   (real component)
-----------------------------------------------------------------------------*/
template <typename num_t>
struct quat_t {
    // data
    num_t q[4];
    
    // Main Constructor
    constexpr quat_t(num_t inX, num_t inY, num_t inZ, num_t inW);
    constexpr quat_t();
    constexpr quat_t(num_t n);
    constexpr quat_t(const quat_t<num_t>& input);
    constexpr quat_t(quat_t<num_t>&& input);
    
    ~quat_t() = default;
    
    // Conversions & Casting
    template <typename other_t>
    constexpr explicit operator quat_t<other_t>() const;
    
    const num_t*    operator    &   () const;
    inline num_t*   operator    &   ();
    
    // Subscripting Operators
    constexpr num_t operator    []  (int i) const;
    inline num_t&   operator    []  (int i);

    //quaternion-quaternion operators
    quat_t&         operator    ++  (); //prefix operators
    quat_t&         operator    --  ();
    quat_t          operator    ++  (int); //postfix operators
    quat_t          operator    --  (int);
    quat_t          operator    +   (const quat_t<num_t>& input) const;
    quat_t          operator    -   (const quat_t<num_t>& input) const;
    quat_t          operator    *   (const quat_t<num_t>& input) const;
    quat_t&         operator    =   (const quat_t<num_t>& input);
    quat_t&         operator    =   (quat_t<num_t>&& input);
    quat_t&         operator    +=  (const quat_t<num_t>& input);
    quat_t&         operator    -=  (const quat_t<num_t>& input);
    quat_t&         operator    *=  (const quat_t<num_t>& input);
    bool            operator    ==  (const quat_t<num_t>& input) const;
    bool            operator    !=  (const quat_t<num_t>& input) const;

    //quaternion-scalar operators
    quat_t          operator    +   (num_t) const;
    quat_t          operator    -   (num_t) const;
    quat_t          operator    *   (num_t) const;
    quat_t          operator    /   (num_t) const;
    quat_t&         operator    =   (num_t);
    quat_t&         operator    +=  (num_t);
    quat_t&         operator    -=  (num_t);
    quat_t&         operator    *=  (num_t);
    quat_t&         operator    /=  (num_t);
};

/*-------------------------------------
    Quaternion Template Specializations
-------------------------------------*/
LS_DECLARE_STRUCT_TYPE(quatf,    quat_t, float);
LS_DECLARE_STRUCT_TYPE(quatd,    quat_t, double);
LS_DECLARE_STRUCT_TYPE(quati,    quat_t, int); // not recommended
LS_DECLARE_STRUCT_TYPE(quatui,   quat_t, unsigned); // not recommended
LS_DECLARE_STRUCT_TYPE(quatx,    quat_t, medp_t);
LS_DECLARE_STRUCT_TYPE(quat,     quat_t, LS_FLOAT);

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/quat_impl.h"

#endif /* __LS_MATH_QUAT_H__ */
