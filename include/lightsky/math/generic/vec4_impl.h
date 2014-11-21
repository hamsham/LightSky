
namespace ls {
namespace math {

/*-------------------------------------
    Constructors
-------------------------------------*/
// Main Constructor
template <typename num_t>
constexpr vec4_t<num_t>::vec4_t(num_t inX, num_t inY, num_t inZ, num_t inW) :
    v{inX, inY, inZ, inW}
{}

template <typename num_t>
constexpr vec4_t<num_t>::vec4_t() :
    v{num_t{0}, num_t{0}, num_t{0}, num_t{0}}
{}

template <typename num_t>
constexpr vec4_t<num_t>::vec4_t(num_t n) :
    v{n, n, n, n}
{}

template <typename num_t>
constexpr vec4_t<num_t>::vec4_t(const vec4_t<num_t>& v) :
    v{v.v[0], v.v[1], v.v[2], v.v[3]}
{}

template <typename num_t>
constexpr vec4_t<num_t>::vec4_t(vec4_t<num_t>&& v) :
    v{v.v[0], v.v[1], v.v[2], v.v[3]}
{}

/*-------------------------------------
    Conversions & Casting
-------------------------------------*/
template <typename num_t>
template <typename other_t>
constexpr vec4_t<num_t>::operator vec4_t<other_t>() const {
    return vec4_t<other_t>{
        (other_t)v[0], (other_t)v[1], (other_t)v[2], (other_t)v[3]
    };
}

template <typename num_t>
const num_t* vec4_t<num_t>::operator&() const {
    return v;
}

template <typename num_t>
inline num_t* vec4_t<num_t>::operator&() {
    return v;
}

/*-------------------------------------
    Subscripting Operators
-------------------------------------*/
template <typename num_t>
constexpr num_t vec4_t<num_t>::operator[] (int i) const {
    return v[i];
}

template <typename num_t>
inline num_t& vec4_t<num_t>::operator[] (int i) {
    return v[i];
}

/*-------------------------------------
    Vector-Vector Math Operations
-------------------------------------*/
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator + (const vec4_t<num_t>& input) const {
    return vec4_t{
        v[0] + input.v[0],
        v[1] + input.v[1],
        v[2] + input.v[2],
        v[3] + input.v[3]
    };
}

template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator - (const vec4_t<num_t>& input) const {
    return vec4_t{
        v[0] - input.v[0],
        v[1] - input.v[1],
        v[2] - input.v[2],
        v[3] - input.v[3]
    };
}

//for operations like "vectA = -vectB"
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator - () const {
    return vec4_t<num_t>{-v[0], -v[1], -v[2], -v[3]};
}

template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator * (const vec4_t<num_t>& input) const {
    return vec4_t<num_t>{
        v[0] * input.v[0],
        v[1] * input.v[1],
        v[2] * input.v[2],
        v[3] * input.v[3]
    };
}

template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator / (const vec4_t<num_t>& input) const {
    return vec4_t<num_t>{
        v[0] / input.v[0],
        v[1] / input.v[1],
        v[2] / input.v[2],
        v[3] / input.v[3]
    };
}

template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator = (const vec4_t<num_t>& input) {
    v[0] = input.v[0];
    v[1] = input.v[1];
    v[2] = input.v[2];
    v[3] = input.v[3];
    return *this;
}

template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator = (vec4_t<num_t>&& input) {
    v[0] = input.v[0];
    v[1] = input.v[1];
    v[2] = input.v[2];
    v[3] = input.v[3];
    return *this;
}

template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator += (const vec4_t<num_t>& input) {
    v[0] += input.v[0];
    v[1] += input.v[1];
    v[2] += input.v[2];
    v[3] += input.v[3];
    return *this;
}

template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator -= (const vec4_t<num_t>& input) {
    v[0] -= input.v[0];
    v[1] -= input.v[1];
    v[2] -= input.v[2];
    v[3] -= input.v[3];
    return *this;
}

template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator *= (const vec4_t<num_t>& input) {
    v[0] *= input.v[0];
    v[1] *= input.v[1];
    v[2] *= input.v[2];
    v[3] *= input.v[3];
    return *this;
}

template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator /= (const vec4_t<num_t>& input) {
    v[0] /= input.v[0];
    v[1] /= input.v[1];
    v[2] /= input.v[2];
    v[3] /= input.v[3];
    return *this;
}

// prefix operations
template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator++ () {
    ++v[0];
    ++v[1];
    ++v[2];
    ++v[3];
    return *this;
}
template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator-- () {
    --v[0];
    --v[1];
    --v[2];
    --v[3];
    return *this;
}

//postfix operations
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator++ (int) {
    return vec4_t<num_t>{
        ++v[0],
        ++v[1],
        ++v[2],
        ++v[3]
    };
}
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator-- (int) {
    return vec4_t<num_t>{
        --v[0],
        --v[1],
        --v[2],
        --v[3]
    };
}

//comparisons
template <typename num_t> inline
bool vec4_t<num_t>::operator== (const vec4_t<num_t>& compare) const {
    return
        v[0] == compare.v[0] &&
        v[1] == compare.v[1] &&
        v[2] == compare.v[2] &&
        v[3] == compare.v[3];
}

template <typename num_t> inline
bool vec4_t<num_t>::operator!= (const vec4_t<num_t>& compare) const {
    return
        v[0] != compare.v[0] ||
        v[1] != compare.v[1] ||
        v[2] != compare.v[2] ||
        v[3] != compare.v[3];
}

template <typename num_t> inline
bool vec4_t<num_t>::operator< (const vec4_t<num_t>& compare) const {
    return
        v[0] < compare.v[0] &&
        v[1] < compare.v[1] &&
        v[2] < compare.v[2] &&
        v[3] < compare.v[3];
}

template <typename num_t> inline
bool vec4_t<num_t>::operator> (const vec4_t<num_t>& compare) const {
    return
        v[0] > compare.v[0] &&
        v[1] > compare.v[1] &&
        v[2] > compare.v[2] &&
        v[3] > compare.v[3];
}

template <typename num_t> inline
bool vec4_t<num_t>::operator<= (const vec4_t<num_t>& compare) const {
    return
        v[0] <= compare.v[0] &&
        v[1] <= compare.v[1] &&
        v[2] <= compare.v[2] &&
        v[3] <= compare.v[3];
}

template <typename num_t> inline
bool vec4_t<num_t>::operator>= (const vec4_t<num_t>& compare) const {
    return
        v[0] >= compare.v[0] &&
        v[1] >= compare.v[1] &&
        v[2] >= compare.v[2] &&
        v[3] >= compare.v[3];
}

/*-------------------------------------
    Vector-Scalar Math Operations
-------------------------------------*/
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator = (num_t input) {
    v[0] = input;
    v[1] = input;
    v[2] = input;
    v[3] = input;
    return *this;
}
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator + (num_t input) const {
    return vec4_t<num_t>{
        v[0] + input,
        v[1] + input,
        v[2] + input,
        v[3] + input
    };
}
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator - (num_t input) const {
    return vec4_t<num_t>{
        v[0] - input,
        v[1] - input,
        v[2] - input,
        v[3] - input
    };
}
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator * (num_t input) const {
    return vec4_t<num_t>{
        v[0] * input,
        v[1] * input,
        v[2] * input,
        v[3] * input
    };
}
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator / (num_t input) const {
    return vec4_t<num_t>{
        v[0] / input,
        v[1] / input,
        v[2] / input,
        v[3] / input
    };
}
template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator += (num_t input) {
    v[0] += input;
    v[1] += input;
    v[2] += input;
    v[3] += input;
    return *this;
}
template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator -= (num_t input) {
    v[0] -= input;
    v[1] -= input;
    v[2] -= input;
    v[3] -= input;
    return *this;
}
template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator *= (num_t input) {
    v[0] *= input;
    v[1] *= input;
    v[2] *= input;
    v[3] *= input;
    return *this;
}
template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator /= (num_t input) {
    v[0] /= input;
    v[1] /= input;
    v[2] /= input;
    v[3] /= input;
    return *this;
}

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
template <typename num_t> inline
vec4_t<num_t> operator + (num_t n, const vec4_t<num_t>& v) {
    return v + n;
}

template <typename num_t> inline
vec4_t<num_t> operator - (num_t n, const vec4_t<num_t>& v) {
    return v - n;
}

template <typename num_t> inline
vec4_t<num_t> operator * (num_t n, const vec4_t<num_t>& v) {
    return v * n;
}

} // end math namespace
} // end ls namespace
