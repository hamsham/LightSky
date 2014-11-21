
namespace ls {
namespace math {

/*-----------------------------------------------------------------------------
    Fixed-Point Class Methods
-----------------------------------------------------------------------------*/
/*
 *  Constructor
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::fixed_t() :
    number{}
{}

/*
 *  Copy Constructor
 *  
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(const fixed_t& f) :
    number{f.number}
{}

/*
 *  Move Constructor
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(fixed_t&& f) :
    number{std::move(f)}
{}

/*
 *  Numeric Constructor
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(fixed_base_t f) :
    number{f}
{}

/*
 *  Constructor
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(float f) :
    number{(fixed_base_t{1} << num_frac_digits) * (fixed_base_t)f}
{}

/*
 *  Constructor
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(double d) :
    number{(fixed_base_t{1} << num_frac_digits) * (fixed_base_t)d}
{}

/*
 *  Pre-Increment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator ++() {
    ++number;
    return *this;
}

/*
 *  Pre-Decrement operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator --() {
    --number;
    return *this;
}

/*
 *  Post-Increment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator ++(int) {
    return fixed_t{number++};
}

/*
 *  Post-Decrement operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator --(int) {
    return fixed_t(number--);
}

/*
 *  Arithmetic "not" operator.
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
bool fixed_t<fixed_base_t, num_frac_digits>::operator !() const {
    return !number;
}

/*
 *  Equivalence operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
bool fixed_t<fixed_base_t, num_frac_digits>::operator ==(const fixed_t& f) const {
    return number == f.number;
}

/*
 *  Non-Equivalence operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
bool fixed_t<fixed_base_t, num_frac_digits>::operator !=(const fixed_t& f) const {
    return number != f.number;
}

/*
 *  Greater than or equal to operator.
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
bool fixed_t<fixed_base_t, num_frac_digits>::operator >=(const fixed_t& f) const {
    return number >= f.number;
}

/*
 *  Less than or equal to operator.
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
bool fixed_t<fixed_base_t, num_frac_digits>::operator <=(const fixed_t& f) const {
    return number <= f.number;
}

/*
 *  Greater than operator.
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
bool fixed_t<fixed_base_t, num_frac_digits>::operator>(const fixed_t& f) const {
    return number > f.number;
}

/*
 *  Less than operator.
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
bool fixed_t<fixed_base_t, num_frac_digits>::operator<(const fixed_t& f) const {
    return number < f.number;
}

/*
 *  Addition operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator +(const fixed_t& f) const {
    return fixed_t{number + f.number};
}

/*
 *  Subtraction operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator -(const fixed_t& f) const {
    return fixed_t{number - f.number};
}

/*
 *  Negation operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator -() const {
    return fixed_t{-number};
}

/*
 *  Multiplication operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator *(const fixed_t& f) const {
    return fixed_t{number * f.number};
}

/*
 *  Division operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator /(const fixed_t& f) const {
    return fixed_t{number / f.number};
}

/*
 *  Modulus operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator %(const fixed_t& f) const {
    return fixed_t{number % f.number};
}

/*
 *  Logical AND operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator &(const fixed_t& f) const {
    return fixed_t{number & f.number};
}

/*
 *  Logical OR operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator |(const fixed_t& f) const {
    return fixed_t{number | f.number};
}

/*
 *  Logical XOR operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator ^ (const fixed_t& f) const {
    return fixed_t{number ^ f.number};
}

/*
 *  Logical NOT operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator ~() const {
    return fixed_t{~number};
}

/*
 *  Shift-Right operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator >>(int n) const {
    return fixed_t{number >> n};
}

/*
 *  Shift-Left operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator <<(int n) const {
    return fixed_t{number << n};
}

/*
 *  Copy-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator =(const fixed_t& f) {
    number = f.number;
    return *this;
}

/*
 *  Move-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator =(fixed_t&& f) {
    number = std::move(f.number);
    return *this;
}

/*
 *  Addition-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator +=(const fixed_t& f) {
    number += f.number;
    return *this;
}

/*
 *  Subtraction-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator -=(const fixed_t& f) {
    number -= f.number;
    return *this;
}

/*
 *  Multiplication-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator *=(const fixed_t& f) {
    number *= f.number;
    return *this;
}

/*
 *  Division-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator /=(const fixed_t& f) {
    number /= f.number;
    return *this;
}

/*
 *  Modulo-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator %=(const fixed_t& f) {
    number %= f.number;
    return *this;
}

/*
 *  Logical AND-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator &=(const fixed_t& f) {
    number &= f.number;
    return *this;
}

/*
 *  Logical OR-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator |=(const fixed_t& f) {
    number |= f.number;
    return *this;
}

/*
 *  Logical XOR-Assignment operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator ^=(const fixed_t& f) {
    number ^= f.number;
    return *this;
}

/*
 *  Shift-Right and Assign operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator >>=(int n) {
    number >>= n;
    return *this;
}

/*
 *  Shift-Left and Assign operator
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator <<=(int n) {
    number <<= n;
    return *this;
}

/*
 *  Single-Precision floating-point cast.
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::operator float() const {
    return float(1.f / (fixed_base_t{1} << num_frac_digits)) * number;
}

/*
 *  Double-Precision floating-point cast.
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::operator double() const {
    return double(1.0 / (fixed_base_t{1} << num_frac_digits)) * number;
}

/*
 *  Integer cast.
 */
template <typename fixed_base_t, unsigned num_frac_digits> constexpr
fixed_t<fixed_base_t, num_frac_digits>::operator fixed_base_t() const {
    return num_frac_digits;
}

/*
 *  Single-Precision floating-point Assignment.
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator =(float f) {
    return *this = fixed_t{f};
}

/*
 *  Double-Precision floating-point Assignment.
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator =(double d) {
    return *this = fixed_t{d};
}

/*
 *  Integral Assignment.
 */
template <typename fixed_base_t, unsigned num_frac_digits> inline
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator =(fixed_base_t f) {
    return *this = fixed_t{f};
}

}//end math namespace
}//end ls namespace