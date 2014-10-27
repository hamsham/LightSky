
namespace ls {
namespace math {

/*-------------------------------------
    Constructors
-------------------------------------*/
// Main Constructor
template <typename num_t>
constexpr mat2_t<num_t>::mat2_t(
    num_t inXX, num_t inXY,
    num_t inYX, num_t inYY
) :
    m{
        {inXX, inXY},
        {inYX, inYY},
    }
{}

template <typename num_t>
constexpr mat2_t<num_t>::mat2_t() :
    m{
        {num_t{0}, num_t{0}},
        {num_t{0}, num_t{0}}
    }
{}

template <typename num_t>
constexpr mat2_t<num_t>::mat2_t(num_t n) :
    m{
        {n,         num_t{0}},
        {num_t{0},  n}
    }
{}

template <typename num_t>
constexpr mat2_t<num_t>::mat2_t(
    const vec2_t<num_t>& x,
    const vec2_t<num_t>& y
) :
    m{
        {x.v[0], x.v[1]},
        {y.v[0], y.v[1]}
    }
{}

template <typename num_t>
constexpr mat2_t<num_t>::mat2_t(const mat2_t<num_t>& m) :
    m{
        {m.m[0][0], m.m[0][1]},
        {m.m[1][0], m.m[1][1]}
    }
{}

template <typename num_t>
constexpr mat2_t<num_t>::mat2_t(mat2_t<num_t>&& m) :
    m{
        {m.m[0][0], m.m[0][1]},
        {m.m[1][0], m.m[1][1]}
    }
{}

/*-------------------------------------
    Conversions & Casting
-------------------------------------*/
template <typename num_t>
template <typename other_t>
constexpr mat2_t<num_t>::operator mat2_t<other_t>() const {
    return mat2_t<other_t>{
        (other_t)m[0][0], (other_t)m[0][1],
        (other_t)m[1][0], (other_t)m[1][1]
    };
}

/*-------------------------------------
    Subscripting Operators
-------------------------------------*/
template <typename num_t>
inline const vec2_t<num_t>& mat2_t<num_t>::operator[](int i) const {
    return m[i];
}

template <typename num_t>
inline vec2_t<num_t>& mat2_t<num_t>::operator[](int i) {
    return m[i];
}

/*-------------------------------------
    Matrix-Matrix Operators
-------------------------------------*/
// prefix operators
template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator++ () {
    ++m[0][0]; ++m[0][1];
    ++m[1][0]; ++m[1][1];
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator-- () {
    --m[0][0]; --m[0][1];
    --m[1][0]; --m[1][1];
    return *this;
}

//postfix operators
template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator++ (int) {
    return mat2_t<num_t>{
        ++m[0][0], ++m[0][1],
        ++m[1][0], ++m[1][1]
    };
}

template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator-- (int) {
    return mat2_t<num_t>{
        --m[0][0], --m[0][1],
        --m[1][0], --m[1][1]
    };
}

template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator + (const mat2_t<num_t>& input) const {
    return mat2_t<num_t>{
        m[0][0] + input.m[0][0], m[0][1] + input.m[0][1],
        m[1][0] + input.m[1][0], m[1][1] + input.m[1][1]
    };
}

template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator - (const mat2_t<num_t>& input) const {
    return mat2_t<num_t>{
        m[0][0] - input.m[0][0], m[0][1] - input.m[0][1],
        m[1][0] - input.m[1][0], m[1][1] - input.m[1][1]
    };
}

//for operations like "mat2a = -mat2b"
template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator - () const {
    return mat2_t<num_t>{
        -m[0][0], -m[0][1],
        -m[1][0], -m[1][1]
    };
}

template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator * (const mat2_t<num_t>& input) const {
    return mat2_t<num_t>{
    //X
        (input.m[0][0]*m[0][0]) + (input.m[0][1]*m[1][0]),
        (input.m[0][0]*m[0][1]) + (input.m[0][1]*m[1][1]),
    //Y
        (input.m[1][0]*m[0][0]) + (input.m[1][1]*m[1][0]),
        (input.m[1][0]*m[0][1]) + (input.m[1][1]*m[1][1])
    };
}

template <typename num_t>
mat2_t<num_t>& mat2_t<num_t>::operator =(const mat2_t<num_t>& input) {
    m[0][0] = input.m[0][0];
    m[0][1] = input.m[0][1];
    
    m[1][0] = input.m[1][0];
    m[1][1] = input.m[1][1];
    
    return *this;
}

template <typename num_t>
mat2_t<num_t>& mat2_t<num_t>::operator =(mat2_t<num_t>&& input) {
    m[0][0] = input.m[0][0];
    m[0][1] = input.m[0][1];
    
    m[1][0] = input.m[1][0];
    m[1][1] = input.m[1][1];
    
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator += (const mat2_t<num_t>& input) {
    m[0][0] += input.m[0][0]; m[0][1] += input.m[0][1];
    m[1][0] += input.m[1][0]; m[1][1] += input.m[1][1];
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator -= (const mat2_t<num_t>& input) {
    m[0][0] -= input.m[0][0]; m[0][1] -= input.m[0][1];
    m[1][0] -= input.m[1][0]; m[1][1] -= input.m[1][1];
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator *= (const mat2_t<num_t>& input) {
    return *this = *this * input;
}

template <typename num_t> inline
bool mat2_t<num_t>::operator == (const mat2_t<num_t>& compare) const {
    return
        m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] &&
        m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1];
}

template <typename num_t> inline
bool mat2_t<num_t>::operator != (const mat2_t<num_t>& compare) const {
    return
        m[0][0] != compare.m[0][0] || m[0][1] != compare.m[0][1] ||
        m[1][0] != compare.m[1][0] || m[1][1] != compare.m[1][1];
}

/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the vector header)
-------------------------------------*/
template <typename num_t> inline
mat2_t<num_t> vec2_t<num_t>::operator + (const mat2_t<num_t>& m) const {
    return mat2_t<num_t>{
        v[0] + m.m[0][0], v[0] + m.m[0][1],
        v[1] + m.m[1][0], v[1] + m.m[1][1]
    };
}

template <typename num_t> inline
mat2_t<num_t> vec2_t<num_t>::operator - (const mat2_t<num_t>& m) const {
    return mat2_t<num_t>{
        v[0] - m.m[0][0], v[0] - m.m[0][1],
        v[1] - m.m[1][0], v[1] - m.m[1][1]
    };
}

// Multiplies by a row vector
template <typename num_t> inline
vec2_t<num_t> vec2_t<num_t>::operator * (const mat2_t<num_t>& m) const {
    return vec2_t<num_t>{
        (m.m[0][0] * v[0]) + (m.m[1][0] * v[1]),
        (m.m[0][1] * v[0]) + (m.m[1][1] * v[1])
    };
}

template <typename num_t> inline
vec2_t<num_t>& vec2_t<num_t>::operator *= (const mat2_t<num_t>& m) {
    *this = *this * m;
    return *this;
}

/*-------------------------------------
    Matrix-Vector Operators
-------------------------------------*/
template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator + (const vec2_t<num_t>& input) const {
    return mat2_t{
        m[0][0] + input.v[0], m[0][1] + input.v[1],
        m[1][0] + input.v[0], m[1][1] + input.v[1]
    };
}

template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator - (const vec2_t<num_t>& input) const {
    return mat2_t{
        m[0][0] - input.v[0], m[0][1] - input.v[1],
        m[1][0] - input.v[0], m[1][1] - input.v[1]
    };
}

// Multiply by a column-vector
template <typename num_t> inline
vec2_t<num_t> mat2_t<num_t>::operator * (const vec2_t<num_t>& inVec) const {
    return vec2_t<num_t>{
        (m[0][0] * inVec.v[0]) + (m[0][1] * inVec.v[1]),
        (m[1][0] * inVec.v[0]) + (m[1][1] * inVec.v[1])
    };
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator = (const vec2_t<num_t>& input) {
    m[0][0] = input.v[0]; m[0][1] = input.v[0];
    m[1][0] = input.v[1]; m[1][1] = input.v[1];
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator += (const vec2_t<num_t>& input) {
    m[0][0] += input.v[0]; m[0][1] += input.v[1];
    m[1][0] += input.v[0]; m[1][1] += input.v[1];
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator -= (const vec2_t<num_t>& input) {
    m[0][0] -= input.v[0]; m[0][1] -= input.v[1];
    m[1][0] -= input.v[0]; m[1][1] -= input.v[1];
    return *this;
}

/*-------------------------------------
    Matrix-Scalar Operators
-------------------------------------*/
template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator + (num_t input) const {
    return mat2_t<num_t>{
        m[0][0] + input, m[0][1] + input,
        m[1][0] + input, m[1][1] + input
    };
}

template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator - (num_t input) const {
    return mat2_t<num_t>{
        m[0][0] - input, m[0][1] - input,
        m[1][0] - input, m[1][1] - input
    };
}

template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator * (num_t input) const {
    return mat2_t<num_t>{
        m[0][0] * input, m[0][1] * input,
        m[1][0] * input, m[1][1] * input
    };
}

template <typename num_t> inline
mat2_t<num_t> mat2_t<num_t>::operator / (num_t input) const {
    return mat2_t<num_t>{
        m[0][0] / input, m[0][1] / input,
        m[1][0] / input, m[1][1] / input
    };
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator = (num_t input) {
    m[0][0] = input; m[0][1] = input;
    m[1][0] = input; m[1][1] = input;
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator += (num_t input) {
    m[0][0] += input; m[0][1] += input;
    m[1][0] += input; m[1][1] += input;
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator -= (num_t input) {
    m[0][0] -= input; m[0][1] -= input;
    m[1][0] -= input; m[1][1] -= input;
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator *= (num_t input) {
    m[0][0] *= input; m[0][1] *= input;
    m[1][0] *= input; m[1][1] *= input;
    return *this;
}

template <typename num_t> inline
mat2_t<num_t>& mat2_t<num_t>::operator /= (num_t input) {
    m[0][0] /= input; m[0][1] /= input;
    m[1][0] /= input; m[1][1] /= input;
    return *this;
}

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> inline
mat2_t<num_t> operator + (num_t n, const mat2_t<num_t>& m) {
    return m + n;
}

template <typename num_t> inline
mat2_t<num_t> operator - (num_t n, const mat2_t<num_t>& m) {
    return m - n;
}

template <typename num_t> inline
mat2_t<num_t> operator * (num_t n, const mat2_t<num_t>& m) {
    return m * n;
}

} //end math namespace
} //end ls namespace
