
namespace ls {
namespace math {

/*-------------------------------------
    Constructors
-------------------------------------*/
// Main Constructor
template <typename num_t>
constexpr mat3_t<num_t>::mat3_t(
    num_t inXX, num_t inXY, num_t inXZ,
    num_t inYX, num_t inYY, num_t inYZ,
    num_t inZX, num_t inZY, num_t inZZ
) :
    m{
        {inXX, inXY, inXZ},
        {inYX, inYY, inYZ},
        {inZX, inZY, inZZ}
    }
{}

template <typename num_t>
constexpr mat3_t<num_t>::mat3_t() :
    m{
        {num_t{0}, num_t{0}, num_t{0}},
        {num_t{0}, num_t{0}, num_t{0}},
        {num_t{0}, num_t{0}, num_t{0}}
    }
{}

template <typename num_t>
constexpr mat3_t<num_t>::mat3_t(num_t n) :
    m{
        {n,         num_t{0},   num_t{0}},
        {num_t{0},  n,          num_t{0}},
        {num_t{0},  num_t{0},   n}
    }
{}

template <typename num_t>
constexpr mat3_t<num_t>::mat3_t(
    const vec3_t<num_t>& x,
    const vec3_t<num_t>& y,
    const vec3_t<num_t>& z
) :
    m{
        {x.v[0], x.v[1], x.v[2]},
        {y.v[0], y.v[1], y.v[2]},
        {z.v[0], z.v[1], z.v[2]}
    }
{}

template <typename num_t>
constexpr mat3_t<num_t>::mat3_t(const mat3_t<num_t>& m) :
    m{
        {m.m[0][0], m.m[0][1], m.m[0][2]},
        {m.m[1][0], m.m[1][1], m.m[1][2]},
        {m.m[2][0], m.m[2][1], m.m[2][2]}
    }
{}

template <typename num_t>
constexpr mat3_t<num_t>::mat3_t(mat3_t<num_t>&& m) :
    m{
        {m.m[0][0], m.m[0][1], m.m[0][2]},
        {m.m[1][0], m.m[1][1], m.m[1][2]},
        {m.m[2][0], m.m[2][1], m.m[2][2]}
    }
{}

/*-------------------------------------
    Conversions & Casting
-------------------------------------*/
template <typename num_t>
template <typename other_t>
constexpr mat3_t<num_t>::operator mat3_t<other_t>() const {
    return mat3_t<other_t>{
        (other_t)m[0][0], (other_t)m[0][1], (other_t)m[0][2],
        (other_t)m[1][0], (other_t)m[1][1], (other_t)m[1][2],
        (other_t)m[2][0], (other_t)m[2][1], (other_t)m[2][2]
    };
}

/*-------------------------------------
    Subscripting Operators
-------------------------------------*/
template <typename num_t>
inline const vec3_t<num_t>& mat3_t<num_t>::operator[](int i) const {
    return m[i];
}

template <typename num_t>
inline vec3_t<num_t>& mat3_t<num_t>::operator[](int i) {
    return m[i];
}

/*-------------------------------------
    Matrix-Matrix Operators
-------------------------------------*/
// prefix operators
template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator++ () {
    ++m[0][0]; ++m[0][1]; ++m[0][2];
    ++m[1][0]; ++m[1][1]; ++m[1][2];
    ++m[2][0]; ++m[2][1]; ++m[2][2];
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator-- () {
    --m[0][0]; --m[0][1]; --m[0][2];
    --m[1][0]; --m[1][1]; --m[1][2];
    --m[2][0]; --m[2][1]; --m[2][2];
    return *this;
}

//postfix operators
template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator++ (int) {
    return mat3_t<num_t>{
        ++m[0][0], ++m[0][1], ++m[0][2],
        ++m[1][0], ++m[1][1], ++m[1][2],
        ++m[2][0], ++m[2][1], ++m[2][2]
    };
}

template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator-- (int) {
    return mat3_t<num_t>{
        --m[0][0], --m[0][1], --m[0][2],
        --m[1][0], --m[1][1], --m[1][2],
        --m[2][0], --m[2][1], --m[2][2]
    };
}

template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator + (const mat3_t<num_t>& input) const {
    return mat3_t<num_t>{
        m[0][0] + input.m[0][0], m[0][1] + input.m[0][1], m[0][2] + input.m[0][2],
        m[1][0] + input.m[1][0], m[1][1] + input.m[1][1], m[1][2] + input.m[1][2],
        m[2][0] + input.m[2][0], m[2][1] + input.m[2][1], m[2][2] + input.m[2][2]
    };
}

template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator - (const mat3_t<num_t>& input) const {
    return mat3_t<num_t>{
        m[0][0] - input.m[0][0], m[0][1] - input.m[0][1], m[0][2] - input.m[0][2],
        m[1][0] - input.m[1][0], m[1][1] - input.m[1][1], m[1][2] - input.m[1][2],
        m[2][0] - input.m[2][0], m[2][1] - input.m[2][1], m[2][2] - input.m[2][2]
    };
}

//for operations like "matrix3a = -matrix3b"
template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator - () const {
    return mat3_t<num_t>{
        -m[0][0], -m[0][1], -m[0][2],
        -m[1][0], -m[1][1], -m[1][2],
        -m[2][0], -m[2][1], -m[2][2]
    };
}

template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator * (const mat3_t<num_t>& input) const {
    return mat3_t<num_t>{
    //X
        (input.m[0][0]*m[0][0]) + (input.m[0][1]*m[1][0]) + (input.m[0][2]*m[2][0]),
        (input.m[0][0]*m[0][1]) + (input.m[0][1]*m[1][1]) + (input.m[0][2]*m[2][1]),
        (input.m[0][0]*m[0][2]) + (input.m[0][1]*m[1][2]) + (input.m[0][2]*m[2][2]),
    //Y
        (input.m[1][0]*m[0][0]) + (input.m[1][1]*m[1][0]) + (input.m[1][2]*m[2][0]),
        (input.m[1][0]*m[0][1]) + (input.m[1][1]*m[1][1]) + (input.m[1][2]*m[2][1]),
        (input.m[1][0]*m[0][2]) + (input.m[1][1]*m[1][2]) + (input.m[1][2]*m[2][2]),
    //Z
        (input.m[2][0]*m[0][0]) + (input.m[2][1]*m[1][0]) + (input.m[2][2]*m[2][0]),
        (input.m[2][0]*m[0][1]) + (input.m[2][1]*m[1][1]) + (input.m[2][2]*m[2][1]),
        (input.m[2][0]*m[0][2]) + (input.m[2][1]*m[1][2]) + (input.m[2][2]*m[2][2])
    };
}

template <typename num_t>
mat3_t<num_t>& mat3_t<num_t>::operator =(const mat3_t<num_t>& input) {
    m[0][0] = input.m[0][0];
    m[0][1] = input.m[0][1];
    m[0][2] = input.m[0][2];
    
    m[1][0] = input.m[1][0];
    m[1][1] = input.m[1][1];
    m[1][2] = input.m[1][2];
    
    m[2][0] = input.m[2][0];
    m[2][1] = input.m[2][1];
    m[2][2] = input.m[2][2];
    
    return *this;
}

template <typename num_t>
mat3_t<num_t>& mat3_t<num_t>::operator =(mat3_t<num_t>&& input) {
    m[0][0] = input.m[0][0];
    m[0][1] = input.m[0][1];
    m[0][2] = input.m[0][2];
    
    m[1][0] = input.m[1][0];
    m[1][1] = input.m[1][1];
    m[1][2] = input.m[1][2];
    
    m[2][0] = input.m[2][0];
    m[2][1] = input.m[2][1];
    m[2][2] = input.m[2][2];
    
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator += (const mat3_t<num_t>& input) {
    m[0][0] += input.m[0][0]; m[0][1] += input.m[0][1]; m[0][2] += input.m[0][2];
    m[1][0] += input.m[1][0]; m[1][1] += input.m[1][1]; m[1][2] += input.m[1][2];
    m[2][0] += input.m[2][0]; m[2][1] += input.m[2][1]; m[2][2] += input.m[2][2];
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator -= (const mat3_t<num_t>& input) {
    m[0][0] -= input.m[0][0]; m[0][1] -= input.m[0][1]; m[0][2] -= input.m[0][2];
    m[1][0] -= input.m[1][0]; m[1][1] -= input.m[1][1]; m[1][2] -= input.m[1][2];
    m[2][0] -= input.m[2][0]; m[2][1] -= input.m[2][1]; m[2][2] -= input.m[2][2];
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator *= (const mat3_t<num_t>& input) {
    return *this = *this * input;
}

template <typename num_t> inline
bool mat3_t<num_t>::operator == (const mat3_t<num_t>& compare) const {
    return
        m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] && m[0][2] == compare.m[0][2] &&
        m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1] && m[1][2] == compare.m[1][2] &&
        m[2][0] == compare.m[2][0] && m[2][1] == compare.m[2][1] && m[2][2] == compare.m[2][2];
}

template <typename num_t> inline
bool mat3_t<num_t>::operator != (const mat3_t<num_t>& compare) const {
    return
        m[0][0] != compare.m[0][0] || m[0][1] != compare.m[0][1] || m[0][2] != compare.m[0][2] ||
        m[1][0] != compare.m[1][0] || m[1][1] != compare.m[1][1] || m[1][2] != compare.m[1][2] ||
        m[2][0] != compare.m[2][0] || m[2][1] != compare.m[2][1] || m[2][2] != compare.m[2][2];
}

/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 3D Vector header)
-------------------------------------*/
template <typename num_t> inline
mat3_t<num_t> vec3_t<num_t>::operator + (const mat3_t<num_t>& m) const {
    return mat3_t<num_t>{
        v[0] + m.m[0][0], v[0] + m.m[0][1], v[0] + m.m[0][2],
        v[1] + m.m[1][0], v[1] + m.m[1][1], v[1] + m.m[1][2],
        v[2] + m.m[2][0], v[2] + m.m[2][1], v[2] + m.m[2][2]
    };
}

template <typename num_t> inline
mat3_t<num_t> vec3_t<num_t>::operator - (const mat3_t<num_t>& m) const {
    return mat3_t<num_t>{
        v[0] - m.m[0][0], v[0] - m.m[0][1], v[0] - m.m[0][2],
        v[1] - m.m[1][0], v[1] - m.m[1][1], v[1] - m.m[1][2],
        v[2] - m.m[2][0], v[2] - m.m[2][1], v[2] - m.m[2][2]
    };
}

// Multiplies by a row vector
template <typename num_t> inline
vec3_t<num_t> vec3_t<num_t>::operator * (const mat3_t<num_t>& m) const {
    return vec3_t<num_t>{
        (m.m[0][0] * v[0]) + (m.m[1][0] * v[1]) + (m.m[2][0] * v[2]),
        (m.m[0][1] * v[0]) + (m.m[1][1] * v[1]) + (m.m[2][1] * v[2]),
        (m.m[0][2] * v[0]) + (m.m[1][2] * v[1]) + (m.m[2][2] * v[2])
    };
}

template <typename num_t> inline
vec3_t<num_t>& vec3_t<num_t>::operator *= (const mat3_t<num_t>& m) {
    *this = *this * m;
    return *this;
}

/*-------------------------------------
    Matrix-Vector Operators
-------------------------------------*/
template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator + (const vec3_t<num_t>& input) const {
    return mat3_t{
        m[0][0] + input.v[0], m[0][1] + input.v[1], m[0][2] + input.v[2],
        m[1][0] + input.v[0], m[1][1] + input.v[1], m[1][2] + input.v[2],
        m[2][0] + input.v[0], m[2][1] + input.v[1], m[2][2] + input.v[2]
    };
}

template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator - (const vec3_t<num_t>& input) const {
    return mat3_t{
        m[0][0] - input.v[0], m[0][1] - input.v[1], m[0][2] - input.v[2],
        m[1][0] - input.v[0], m[1][1] - input.v[1], m[1][2] - input.v[2],
        m[2][0] - input.v[0], m[2][1] - input.v[1], m[2][2] - input.v[2]
    };
}

// Multiply by a column-vector
template <typename num_t> inline
vec3_t<num_t> mat3_t<num_t>::operator * (const vec3_t<num_t>& inVect) const {
    return vec3_t<num_t>{
        (m[0][0] * inVect.v[0]) + (m[0][1] * inVect.v[1]) + (m[0][2] * inVect.v[2]),
        (m[1][0] * inVect.v[0]) + (m[1][1] * inVect.v[1]) + (m[1][2] * inVect.v[2]),
        (m[2][0] * inVect.v[0]) + (m[2][1] * inVect.v[1]) + (m[2][2] * inVect.v[2])
    };
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator = (const vec3_t<num_t>& input) {
    m[0][0] = input.v[0]; m[0][1] = input.v[1]; m[0][2] = input.v[2];
    m[1][0] = input.v[0]; m[1][1] = input.v[1]; m[1][2] = input.v[2];
    m[2][0] = input.v[0]; m[2][1] = input.v[1]; m[2][2] = input.v[2];
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator += (const vec3_t<num_t>& input) {
    m[0][0] += input.v[0]; m[0][1] += input.v[1]; m[0][2] += input.v[2];
    m[1][0] += input.v[0]; m[1][1] += input.v[1]; m[1][2] += input.v[2];
    m[2][0] += input.v[0]; m[2][1] += input.v[1]; m[2][2] += input.v[2];
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator -= (const vec3_t<num_t>& input) {
    m[0][0] -= input.v[0]; m[0][1] -= input.v[1]; m[0][2] -= input.v[2];
    m[1][0] -= input.v[0]; m[1][1] -= input.v[1]; m[1][2] -= input.v[2];
    m[2][0] -= input.v[0]; m[2][1] -= input.v[1]; m[2][2] -= input.v[2];
    return *this;
}

/*-------------------------------------
    Matrix-Scalar Operators
-------------------------------------*/
template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator + (num_t input) const {
    return mat3_t<num_t>(
        m[0][0] + input, m[0][1] + input, m[0][2] + input,
        m[1][0] + input, m[1][1] + input, m[1][2] + input,
        m[2][0] + input, m[2][1] + input, m[2][2] + input
    );
}

template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator - (num_t input) const {
    return mat3_t<num_t>{
        m[0][0] - input, m[0][1] - input, m[0][2] - input,
        m[1][0] - input, m[1][1] - input, m[1][2] - input,
        m[2][0] - input, m[2][1] - input, m[2][2] - input
    };
}

template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator * (num_t input) const {
    return mat3_t<num_t>{
        m[0][0] * input, m[0][1] * input, m[0][2] * input,
        m[1][0] * input, m[1][1] * input, m[1][2] * input,
        m[2][0] * input, m[2][1] * input, m[2][2] * input
    };
}

template <typename num_t> inline
mat3_t<num_t> mat3_t<num_t>::operator / (num_t input) const {
    return mat3_t<num_t>{
        m[0][0] / input, m[0][1] / input, m[0][2] / input,
        m[1][0] / input, m[1][1] / input, m[1][2] / input,
        m[2][0] / input, m[2][1] / input, m[2][2] / input
    };
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator = (num_t input) {
    m[0][0] = input; m[0][1] = input; m[0][2] = input;
    m[1][0] = input; m[1][1] = input; m[1][2] = input;
    m[2][0] = input; m[2][1] = input; m[2][2] = input;
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator += (num_t input) {
    m[0][0] += input; m[0][1] += input; m[0][2] += input;
    m[1][0] += input; m[1][1] += input; m[1][2] += input;
    m[2][0] += input; m[2][1] += input; m[2][2] += input;
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator -= (num_t input) {
    m[0][0] -= input; m[0][1] -= input; m[0][2] -= input;
    m[1][0] -= input; m[1][1] -= input; m[1][2] -= input;
    m[2][0] -= input; m[2][1] -= input; m[2][2] -= input;
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator *= (num_t input) {
    m[0][0] *= input; m[0][1] *= input; m[0][2] *= input;
    m[1][0] *= input; m[1][1] *= input; m[1][2] *= input;
    m[2][0] *= input; m[2][1] *= input; m[2][2] *= input;
    return *this;
}

template <typename num_t> inline
mat3_t<num_t>& mat3_t<num_t>::operator /= (num_t input) {
    m[0][0] /= input; m[0][1] /= input; m[0][2] /= input;
    m[1][0] /= input; m[1][1] /= input; m[1][2] /= input;
    m[2][0] /= input; m[2][1] /= input; m[2][2] /= input;
    return *this;
}

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> inline
mat3_t<num_t> operator + (num_t n, const mat3_t<num_t>& m) {
    return m + n;
}

template <typename num_t> inline
mat3_t<num_t> operator - (num_t n, const mat3_t<num_t>& m) {
    return m - n;
}

template <typename num_t> inline
mat3_t<num_t> operator * (num_t n, const mat3_t<num_t>& m) {
    return m * n;
}

} //end math namespace
} //end ls namespace
