
namespace ls {

/*-----------------------------------------------------------------------------
// Function definitions
-----------------------------------------------------------------------------*/
/*-------------------------------------
    min
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::min(scalar_t a, scalar_t b) {
    return (a < b) ? a : b;
}

/*-------------------------------------
    mix
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::mix(scalar_t a, scalar_t b, scalar_t percent) {
    return a + ((b - a) * percent);
}

/*-------------------------------------
    mac
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::max(scalar_t a, scalar_t b) {
    return (a > b) ? a : b;
}

/*-------------------------------------
    clamp
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::clamp(scalar_t n, scalar_t minVal, scalar_t maxVal) {
    return (n < minVal) ? minVal : (n > maxVal) ? maxVal : n;
}

/*-------------------------------------
    smoothstep
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::smoothstep(scalar_t a, scalar_t b, scalar_t x) {
    if (x <= a) {
        return scalar_t{0};
    }
    else if (x >= b) {
        return scalar_t{1};
    }
    
    const scalar_t t = (x-a)/(b-a);
    return (scalar_t{3}*t*t*t) - (scalar_t{2}*t*t);
}

/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fastInvSqrt(scalar_t input) {
    return (scalar_t) fastInvSqrt<float>((float) input);
}

/*-------------------------------------
    fastSqrt
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fastSqrt(scalar_t input) {
    return scalar_t(1.0f / fastInvSqrt<scalar_t>(input));
}

/*-------------------------------------
    fastInvSqrt
    
    The fast inverse square root method adopted for regular square rooting.
    this method was found at:
        http://rrrola.wz.cz/inv_sqrt.html
    and:
        http://jheriko-rtw.blogspot.com/2009/04/understanding-and-improving-fast.html
-------------------------------------*/
template <> inline
float math::fastInvSqrt<float>(float x) {

    union {
        float f;
        unsigned int u;
    } y = {x};
    y.u = 0x5F1FFFF9ul - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);
}

/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
template <> inline
float math::fastSqrt<float>(float input) {
    return float( 1.0f / fastInvSqrt<float>(input));
}

/*-------------------------------------
    degToRad
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::degToRad(scalar_t input) {
    return LS_DEG2RAD(input);
}

/*-------------------------------------
    radToDeg
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::radToDeg(scalar_t input) {
    return LS_RAD2DEG(input);
}

/*-------------------------------------
    fastLog2
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fastLog2(scalar_t n) {
    return (scalar_t) fastLog2<float>((float) n);
}

/*-------------------------------------
    fastLog2
    
    Fast Approximate logarithms
    This method was found on flipcode:
        http://www.flipcode.com/archives/Fast_log_Function.shtml
    Accurate to within 5 decimal places.
    This method relies on the IEEE floating point specification
-------------------------------------*/
template <> inline
float math::fastLog2<float>(float n) {
    int* const exp = reinterpret_cast<int*> (&n);
    int x = *exp;

    const int log2 = ((x >> 23) & 255) - 128;

    x &= ~(255 << 23);
    x += 127 << 23;

    *exp = x;
    n = ((-1.f / 3.f) * n + 2.f) * n - 2.f / 3.f;
    return n + log2;
}

/*-------------------------------------
    fastLog
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fastLog(scalar_t n) {
    return fastLog2<scalar_t>(n) * 0.693147181f; // ln( 2 )
}

/*-------------------------------------
    fastLogN
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fastLogN(scalar_t baseN, scalar_t n) {
    return fastLog2<scalar_t>(n) / fastLog2<scalar_t>(baseN);
}

/*-------------------------------------
    nextPow2
-------------------------------------*/
inline unsigned math::nextPow2(unsigned n) {
    if (n == 0) {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return ++n;
}

/*-------------------------------------
    nextPow2
-------------------------------------*/
inline int math::nextPow2(int n) {
    return (int)nextPow2((unsigned)n);
}

/*-------------------------------------
    prevPow2
-------------------------------------*/
inline unsigned math::prevPow2(unsigned n) {
    if (n == 0) {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n - (n >> 1);
}

/*-------------------------------------
    prevPow2
-------------------------------------*/
inline int math::prevPow2(int n) {
    return (int)prevPow2((unsigned)n);
}

/*-------------------------------------
    nearPow2
-------------------------------------*/
inline unsigned math::nearPow2(unsigned n) {
    const unsigned pp2 = prevPow2(n);
    const unsigned np2 = nextPow2(n);
    const unsigned lo = n - pp2;
    const unsigned hi = np2 - n;

    return lo < hi ? pp2 : np2;
}

/*-------------------------------------
    nearPow2
-------------------------------------*/
inline int math::nearPow2(int n) {
    return (int)nearPow2((unsigned)n);
}

/*-------------------------------------
    isPow2
-------------------------------------*/
constexpr bool math::isPow2(unsigned n) {
    return n && !(n & (n-1));
}

/*-------------------------------------
    isPow2
-------------------------------------*/
constexpr bool math::isPow2(int n) {
    return (int)isPow2((unsigned)n);
}

/*-------------------------------------
    factorial
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::factorial(scalar_t x) {
    return (1 < x) ? x*factorial(x-1) : 1;
}

/*-------------------------------------
    pow
-------------------------------------*/
template <typename scalar_t, typename int_t>
constexpr scalar_t math::pow(scalar_t x, int_t y) {
    return (0 < y) ? x * pow(x,y-1) : 1;
}

/*-------------------------------------
    const_sin
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::const_sin(scalar_t x) {
    return x
        -(x*x*x*scalar_t(1.f/6))
        +(x*x*x*x*x*scalar_t(1.f/120))
        -(x*x*x*x*x*x*x*scalar_t(1.f/5040))
        +(x*x*x*x*x*x*x*x*x*scalar_t(1.f/362880));
}

/*-------------------------------------
    const_cos
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::const_cos(scalar_t x) {
    return 1
        -(x*x*scalar_t(1.f/2))
        +(x*x*x*x*scalar_t(1.f/4))
        -(x*x*x*x*x*x*scalar_t(1.f/720))
        +(x*x*x*x*x*x*x*x*scalar_t(1.f/40320));
}

/*-------------------------------------
    const_tan
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::const_tan(scalar_t x) {
    return x
        +(x*x*x*scalar_t(1.f/3))
        +(x*x*x*x*x*scalar_t(2.f/15))
        +(x*x*x*x*x*x*x*scalar_t(17.f/315))
        +(x*x*x*x*x*x*x*x*x*scalar_t(62.f/2835));
}

/*-------------------------------------
    sum
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::sum(const scalar_t& num) {
    return num;
}

/*-------------------------------------
    sum
-------------------------------------*/
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t math::sum(const scalar_t& num, const scalars_t&... nums) {
    return num + sum(nums...);
}

/*-------------------------------------
    average
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::average() {
    return scalar_t(0);
}

/*-------------------------------------
    average
-------------------------------------*/
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t math::average(const scalar_t& num, const scalars_t&... nums) {
    return sum(num, nums...) / scalar_t(sizeof...(scalars_t)+1);
}

} /* end ls namespace */
