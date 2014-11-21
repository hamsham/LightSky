
#ifndef __LS_MATH_FIXED_H__
#define __LS_MATH_FIXED_H__

#include <climits> // CHAR_BIT
#include <cstdint>
#include <utility> // std::move()

#include "lightsky/math/setup.h"
#include "lightsky/math/types.h"

namespace ls {
namespace math {

/**----------------------------------------------------------------------------
 *  @brief Fixed-Point number Class.
 *  Utilizes the bits provided by a type from a "fixed_base_t" in order to
 *  store integral values that represent a fixed-precision number.
 *  
 *  In it's current state, it's prone to overflows.
-----------------------------------------------------------------------------*/
template <typename fixed_base_t, unsigned num_frac_digits>
class fixed_t final {
    
    static_assert(
        num_frac_digits < (sizeof(fixed_base_t))*CHAR_BIT,
        "Fixed-Point object has too much precision."
    );
    
    static_assert(
        num_frac_digits != 0,
        "Fixed-Point object has no precision."
    );
    
    private:
        /**
         *  @brief number
         *  The singular piece of data contained within this class which
         *  represents a fractional decimal number using fixed-point
         *  arithmetic.
         */
        fixed_base_t number;

    public:
        /**
         *  @brief Constructors
         *  Initializes all data.
         */
        constexpr fixed_t();
        
        /**
         *  @brief Copy Constructor
         *  
         *  Copies all data from the input parameter into *this.
         *  
         *  @param f
         *  A constant reference to another fixed-point number with the same
         *  precision and bit-count.
         *  
         */
        constexpr fixed_t(const fixed_t& f);
        
        /**
         *  @brief Move Constructor
         *  
         *  Moves data from the input parameter into *this.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         */
        constexpr fixed_t(fixed_t&& f);
        
        /**
         *  @brief Numeric Constructor
         *  
         *  Constructs a fixed-point number using a plain data type.
         *  
         *  @param
         *  An integral type that will be used to construct this object's
         *  internal data.
         *  
         *  
         */
        explicit constexpr fixed_t(fixed_base_t f);
        
        /**
         *  @brief Constructor
         *  
         *  This constructor attempts to create a fixed-point value from a
         *  floating-point decimal value.
         *  
         *  @param
         *  A single-precision floating point number.
         */
        explicit constexpr fixed_t(float f);

        /**
         *  @brief Constructor
         *  
         *  This constructor attempts to create a fixed-point value from a
         *  floating-point decimal value using double-precision.
         *  
         *  @param d
         *  A double precision floating-point number.
         */
        explicit constexpr fixed_t(double d);
        
        /**
         *  @brief Destructor
         *  
         *  Defaulted in order to allow a fixed-precision type to be used in
         *  constexpr expressions.
         */
        ~fixed_t() = default;
        
        /**
         *  @brief Pre-Increment operator
         *  
         *  Increments *this by a factor of 1.
         *  
         *  @return
         *  A reference to *this after it has been incremented.
         */
        inline fixed_t& operator ++();
        
        /**
         *  @brief Pre-Decrement operator
         *  
         *  Decrements *this by a factor of 1.
         *  
         *  @return
         *  A reference to *this after it has been decremented.
         */
        inline fixed_t& operator --();
        
        /**
         *  @brief Post-Increment operator
         *  
         *  Increments *this by a factor of 1.
         *  
         *  @param
         *  unused
         *  
         *  @return
         *  A copy of *this containing the currently contained numerical value
         *  before it has been incremented.
         */
        inline fixed_t operator ++(int);
        
        /**
         *  @brief Post-Decrement operator
         *  
         *  Decrements *this by a factor of 1.
         *  
         *  @param
         *  unused
         *  
         *  @return
         *  A copy of *this containing the currently contained numerical value
         *  before it has been decremented.
         */
        inline fixed_t operator --(int);
        
        /**
         *  @brief Arithmetic "not" operator.
         *  
         *  Determines if this object contains a value equal to 0.
         *  
         *  @return
         *  TRUE if this object contains a value equal to zero, FALSE if
         *  otherwise.
         */
        constexpr bool operator !() const;
        
        /**
         *  @brief Equivalence operator
         *  
         *  Determines if *this object contains a value that is equivalent to
         *  the value contained within the input parameter.
         *  
         *  @param f
         *  Another fixed-point number of the same type as *this.
         *  
         *  @return
         *  TRUE if the numerical values between this and the input parameters
         *  are the same, false if not.
         */
        constexpr bool operator ==(const fixed_t& f) const;
        
        /**
         *  @brief Non-Equivalence operator
         *  
         *  Determines if *this object contains a value that is not equivalent
         *  to the value contained within the input parameter.
         *  
         *  @param f
         *  Another fixed-point number of the same type as *this.
         *  
         *  @return
         *  TRUE if the numerical values between this and the input parameters
         *  are not the same, false if they are.
         */
        constexpr bool operator !=(const fixed_t& f) const;
        
        /**
         *  @brief Greater than or equal to operator.
         *  
         *  Determines if *this object contains a value that is greater than or
         *  equal to the value contained within the input parameter.
         *  
         *  @param f
         *  Another fixed-point number of the same type as *this.
         *  
         *  @return
         *  TRUE *this contains a value greater than or equal to the input
         *  parameter, FALSE if not.
         */
        constexpr bool operator >=(const fixed_t& f) const;
        
        /**
         *  @brief Less than or equal to operator.
         *  
         *  Determines if *this object contains a value that is less than or
         *  equal to the value contained within the input parameter.
         *  
         *  @param f
         *  Another fixed-point number of the same type as *this.
         *  
         *  @return
         *  TRUE *this contains a value less than or equal to the input
         *  parameter, FALSE if not.
         */
        constexpr bool operator <=(const fixed_t& f) const;

        /**
         *  @brief Greater than operator.
         *  
         *  Determines if *this object contains a value that is greater than
         *  the value contained within the input parameter.
         *  
         *  @param f
         *  Another fixed-point number of the same type as *this.
         *  
         *  @return
         *  TRUE *this contains a value greater than the input parameter, FALSE
         *  if not.
         */
        constexpr bool operator>(const fixed_t& f) const;

        /**
         *  @brief Less than operator.
         *  
         *  Determines if *this object contains a value that is less than the
         *  value contained within the input parameter.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  TRUE *this contains a value less than the input parameter, FALSE if
         *  not.
         */
        constexpr bool operator<(const fixed_t& f) const;

        /**
         *  @brief Addition operator
         *  
         *  Adds the current value to another fixed-point number.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A fixed-point number containing the added value of *this and the
         *  input parameter.
         */
        constexpr fixed_t operator +(const fixed_t& f) const;

        /**
         *  @brief Subtraction operator
         *  
         *  Subtracts the current value from another fixed-point number.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A fixed-point number containing the subtracted value of the input
         *  parameter from *this.
         */
        constexpr fixed_t operator -(const fixed_t& f) const;

        /**
         *  @brief Negation operator
         *  
         *  Subtracts the current value from 0.
         *  
         *  @return
         *  A fixed-point number containing the value of *this with its sign
         *  flipped between positive or negative.
         */
        constexpr fixed_t operator -() const;

        /**
         *  @brief Multiplication operator
         *  
         *  Multiplied the current value with another fixed-point number.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A fixed-point number containing the multiplied value of the input
         *  parameter and *this.
         */
        constexpr fixed_t operator *(const fixed_t& f) const;

        /**
         *  @brief Division operator
         *  
         *  Divides the current value by another fixed-point number.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A fixed-point number containing the value of *this, divided by the
         *  input parameter.
         */
        constexpr fixed_t operator /(const fixed_t& f) const;

        /**
         *  @brief Modulus operator
         *  
         *  Retrieves the remainder of a division of *this by another
         *  fixed-point number.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  The remainder of a division of *this by the input parameter.
         */
        constexpr fixed_t operator %(const fixed_t& f) const;

        /**
         *  @brief Logical AND operator
         *  
         *  Performs a logical AND operation on the values contained within
         *  *this and the input parameter.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A fixed-point number with the values of *this and the input
         *  parameter combined using a logical AND.
         */
        constexpr fixed_t operator &(const fixed_t& f) const;

        /**
         *  @brief Logical OR operator
         *  
         *  Performs a logical OR operation on the values contained within
         *  *this and the input parameter.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A fixed-point number with the values of *this and the input
         *  parameter combined using a logical OR.
         */
        constexpr fixed_t operator |(const fixed_t& f) const;

        /**
         *  @brief Logical XOR operator
         *  
         *  Performs a logical XOR operation on the values contained within
         *  *this and the input parameter.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A fixed-point number with the values of *this and the input
         *  parameter combined using a logical XOR.
         */
        constexpr fixed_t operator ^ (const fixed_t& f) const;

        /**
         *  @brief Logical NOT operator
         *  
         *  Performs a logical NOT operation on the value contained within
         *  *this.
         *  
         *  @return
         *  A fixed-point number with the values of *this, after a logical NOT.
         */
        constexpr fixed_t operator ~() const;

        /**
         *  @brief Shift-Right operator
         *  
         *  Shifts all of the bits in *this rightward by a specified number of
         *  times.
         *  
         *  @param n
         *  An integer that determines how many times the bits in *this will be
         *  shifted.
         *  
         *  @return
         *  A fixed-point number with the values of *this shifted to the right
         *  by N number of times.
         */
        constexpr fixed_t operator >>(int n) const;

        /**
         *  @brief Shift-Left operator
         *  
         *  Shifts all of the bits in *this leftward by a specified number of
         *  times.
         *  
         *  @param n
         *  An integer that determines how many times the bits in *this will be
         *  shifted.
         *  
         *  @return
         *  A fixed-point number with the values of *this shifted to the left
         *  by N number of times.
         */
        constexpr fixed_t operator <<(int n) const;

        /**
         *  @brief Copy-Assignment operator
         *  
         *  Assigns the value in *this to the one contained within the input
         *  parameter.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after having it's internal value assigned to
         *  the value in the input parameter.
         */
        inline fixed_t& operator =(const fixed_t& f);

        /**
         *  @brief Move-Assignment operator
         *  
         *  Assigns the value in *this to the one contained within the input
         *  parameter by moving instead of copying.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after having it's internal value assigned to
         *  the value in the input parameter through a move operation.
         */
        inline fixed_t& operator =(fixed_t&& f);

        /**
         *  @brief Addition-Assignment operator
         *  
         *  Assigns the value in *this to the one in the input parameter after
         *  combining both values through addition.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after having it's internal value added to the
         *  value in the input parameter.
         */
        inline fixed_t& operator +=(const fixed_t& f);

        /**
         *  @brief Subtraction-Assignment operator
         *  
         *  Assigns the value in *this to the one in the input parameter after
         *  combining both values through subtraction.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after having it's internal value subtracted by
         *  the value in the input parameter.
         */
        inline fixed_t& operator -=(const fixed_t& f);

        /**
         *  @brief Multiplication-Assignment operator
         *  
         *  Assigns the value in *this to the one in the input parameter after
         *  combining both values through multiplication.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after having it's internal value multiplied by
         *  the value in the input parameter.
         */
        inline fixed_t& operator *=(const fixed_t& f);

        /**
         *  @brief Division-Assignment operator
         *  
         *  Assigns the value in *this to the one in the input parameter after
         *  combining both values through division.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after having it's internal value divided by
         *  the value in the input parameter.
         */
        inline fixed_t& operator /=(const fixed_t& f);

        /**
         *  @brief Modulo-Assignment operator
         *  
         *  Divides *this by the input parameter and assigns the value of the
         *  remainder into *this.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after having it's internal value divided by
         *  the input parameter and assigned to the division remainder.
         */
        inline fixed_t& operator %=(const fixed_t& f);

        /**
         *  @brief Logical AND-Assignment operator
         *  
         *  Assigns the value of a logical AND, between *this and the input
         *  parameter, into *this.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after a logical AND operation with the input
         *  parameter.
         */
        inline fixed_t& operator &=(const fixed_t& f);

        /**
         *  @brief Logical OR-Assignment operator
         *  
         *  Assigns the value of a logical OR, between *this and the input
         *  parameter, into *this.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after a logical OR operation with the input
         *  parameter.
         */
        inline fixed_t& operator |=(const fixed_t& f);

        /**
         *  @brief Logical XOR-Assignment operator
         *  
         *  Assigns the value of a logical XOR, between *this and the input
         *  parameter, into *this.
         *  
         *  @param f
         *  A fixed-point number of the same type as *this.
         *  
         *  @return
         *  A reference to *this after a logical XOR operation with the input
         *  parameter.
         */
        inline fixed_t& operator ^=(const fixed_t& f);

        /**
         *  @brief Shift-Right and Assign operator
         *  
         *  Assigns the value of a right shift back into *this.
         *  
         *  @param n
         *  An integral type which denotes the number of times to shift the
         *  value contained within *this.
         *  
         *  @return
         *  A reference to *this after having its bits shifted rightward by N
         *  number of times.
         */
        inline fixed_t& operator >>=(int n);

        /**
         *  @brief Shift-Left and Assign operator
         *  
         *  Assigns the value of a left shift back into *this.
         *  
         *  @param n
         *  An integral type which denotes the number of times to shift the
         *  value contained within *this.
         *  
         *  @return
         *  A reference to *this after having its bits shifted leftward by N
         *  number of times.
         */
        inline fixed_t& operator <<=(int n);

        /**
         *  @brief Single-Precision floating-point cast.
         *  
         *  Converts *this object's internal value into a single-precision
         *  floating-point value.
         *  
         *  @return
         *  A single-precision floating-point value with an approximate value
         *  of *this.
         */
        constexpr operator float() const;

        /**
         *  @brief Double-Precision floating-point cast.
         *  
         *  Converts *this object's internal value into a double-precision
         *  floating-point value.
         *  
         *  @return
         *  A double-precision floating-point value with an approximate value
         *  of *this.
         */
        explicit constexpr operator double() const;

        /**
         *  @brief Integer cast.
         *  
         *  Converts *this object's internal value into an integer, preserving
         *  the fixed-point representation.
         *  
         *  @return
         *  An integer containing the same value as *this with no conversion of
         *  fractions.
         */
        explicit constexpr operator fixed_base_t() const;

        /**
         *  @brief Single-Precision floating-point Assignment.
         *  
         *  Assigns *this to an approximate value of a single-precision float.
         *  
         *  @param f
         *  A single-precision float
         *  
         *  @return
         *  A reference to *this after being converted from a float.
         */
        inline fixed_t& operator =(float f);

        /**
         *  @brief Double-Precision floating-point Assignment.
         *  
         *  Assigns *this to an approximate value of a double-precision float.
         *  
         *  @param f
         *  A double-precision float
         *  
         *  @return
         *  A reference to *this after being converted from a double.
         */
        inline fixed_t& operator =(double d);

        /**
         *  @brief Integral Assignment.
         *  
         *  Assigns *this to the exact value of an integral type
         *  
         *  @param f
         *  An integral type.
         *  
         *  @return
         *  A reference to *this after being assigned to the same value as an
         *  integer.
         */
        inline fixed_t& operator =(fixed_base_t f);
};

/*-------------------------------------
    Fixed-Point Template Specializations
-------------------------------------*/
LS_DECLARE_CLASS_TYPE(lowp_t,           fixed_t,    int32_t,    7); // 24.7 (-1 for the sign)
LS_DECLARE_CLASS_TYPE(lowp,             fixed_t,    LS_INT,     7);
LS_DECLARE_CLASS_TYPE(medp_t,           fixed_t,    int32_t,    15); // 16.15
LS_DECLARE_CLASS_TYPE(medp,             fixed_t,    LS_INT,     15);
LS_DECLARE_CLASS_TYPE(highp_t,          fixed_t,    int32_t,    23); // 8.23
LS_DECLARE_CLASS_TYPE(highp,            fixed_t,    LS_INT,     23);

LS_DECLARE_CLASS_TYPE(long_lowp_t,      fixed_t,    int64_t,    15); // 48.15
LS_DECLARE_CLASS_TYPE(long_medp_t,      fixed_t,    int64_t,    31); // 32.31
LS_DECLARE_CLASS_TYPE(long_highp_t,     fixed_t,    int64_t,    47); // 16.47

LS_DECLARE_CLASS_TYPE(ulowp_t,          fixed_t,    uint32_t,   8); // 24.8 (-1 for the sign)
LS_DECLARE_CLASS_TYPE(ulowp,            fixed_t,    LS_UINT,    8);
LS_DECLARE_CLASS_TYPE(umedp_t,          fixed_t,    uint32_t,   16); // 16.16
LS_DECLARE_CLASS_TYPE(umedp,            fixed_t,    LS_UINT,    16);
LS_DECLARE_CLASS_TYPE(uhighp_t,         fixed_t,    uint32_t,   24); // 8.24
LS_DECLARE_CLASS_TYPE(uhigh,            fixed_t,    LS_UINT,    24);

LS_DECLARE_CLASS_TYPE(ulong_lowp_t,     fixed_t,    uint64_t,   16); // 48.16
LS_DECLARE_CLASS_TYPE(ulong_medp_t,     fixed_t,    uint64_t,   32); // 32.32
LS_DECLARE_CLASS_TYPE(ulong_highp_t,    fixed_t,    uint64_t,   48); // 16.48

}//end math namespace
}//end ls namespace

#include "lightsky/math/generic/fixed_impl.h"

#endif    /* __LS_MATH_FIXED_H__ */
