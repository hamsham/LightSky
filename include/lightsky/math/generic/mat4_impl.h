
namespace ls {
namespace math {

/*-------------------------------------
    Constructors
-------------------------------------*/
// Main Constructor
template <typename num_t>
constexpr mat4_t<num_t>::mat4_t(
    num_t inXX, num_t inXY, num_t inXZ, num_t inXW,
    num_t inYX, num_t inYY, num_t inYZ, num_t inYW,
    num_t inZX, num_t inZY, num_t inZZ, num_t inZW,
    num_t inWX, num_t inWY, num_t inWZ, num_t inWW) :
    m{
        {inXX, inXY, inXZ, inXW},
        {inYX, inYY, inYZ, inYW},
        {inZX, inZY, inZZ, inZW},
        {inWX, inWY, inWZ, inWW}
    }
{}

template <typename num_t>
constexpr mat4_t<num_t>::mat4_t() :
    m{
        {num_t{0}, num_t{0}, num_t{0}, num_t{0}},
        {num_t{0}, num_t{0}, num_t{0}, num_t{0}},
        {num_t{0}, num_t{0}, num_t{0}, num_t{0}},
        {num_t{0}, num_t{0}, num_t{0}, num_t{0}}
    }
{}

template <typename num_t>
constexpr mat4_t<num_t>::mat4_t(num_t n) :
    mat4_t(
        n,          num_t{0},   num_t{0},   num_t{0},
        num_t{0},   n,          num_t{0},   num_t{0},
        num_t{0},   num_t{0},   n,          num_t{0},
        num_t{0},   num_t{0},   num_t{0},   n
    )
{}

template <typename num_t>
constexpr mat4_t<num_t>::mat4_t(const mat3_t<num_t>& input) :
    m{
        {input.m[0][0], input.m[0][1],  input.m[0][2],  num_t{0}},
        {input.m[1][0], input.m[1][1],  input.m[1][2],  num_t{0}},
        {input.m[2][0], input.m[2][1],  input.m[2][2],  num_t{0}},
        {num_t{0},      num_t{0},       num_t{0},       num_t{1}}
    }
{}

template <typename num_t>
constexpr mat4_t<num_t>::mat4_t(mat3_t<num_t>&& input) :
    m{
        {input.m[0][0], input.m[0][1],  input.m[0][2],  num_t{0}},
        {input.m[1][0], input.m[1][1],  input.m[1][2],  num_t{0}},
        {input.m[2][0], input.m[2][1],  input.m[2][2],  num_t{0}},
        {num_t{0},      num_t{0},       num_t{0},       num_t{1}}
    }
{}

template <typename num_t>
constexpr mat4_t<num_t>::mat4_t(
    const vec4_t<num_t>& x,
    const vec4_t<num_t>& y,
    const vec4_t<num_t>& z,
    const vec4_t<num_t>& w
) :
    m{
        {x.v[0], x.v[1], x.v[2], x.v[3]},
        {y.v[0], y.v[1], y.v[2], y.v[3]},
        {z.v[0], z.v[1], z.v[2], z.v[3]},
        {w.v[0], w.v[1], w.v[2], w.v[3]}
    }
{}

template <typename num_t>
constexpr mat4_t<num_t>::mat4_t(const mat4_t<num_t>& m) :
    m{
        {m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]},
        {m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]},
        {m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]},
        {m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]}
    }
{}

template <typename num_t>
constexpr mat4_t<num_t>::mat4_t(mat4_t<num_t>&& m) :
    m{
        {m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]},
        {m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]},
        {m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]},
        {m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]}
    }
{}

/*-------------------------------------
    Conversions & Casting
-------------------------------------*/
template <typename num_t>
template <typename other_t>
constexpr mat4_t<num_t>::operator mat4_t<other_t>() const {
    return mat4_t<other_t>{
        (other_t)m[0][0], (other_t)m[0][1], (other_t)m[0][2], (other_t)m[0][3],
        (other_t)m[1][0], (other_t)m[1][1], (other_t)m[1][2], (other_t)m[1][3],
        (other_t)m[2][0], (other_t)m[2][1], (other_t)m[2][2], (other_t)m[2][3],
        (other_t)m[3][0], (other_t)m[3][1], (other_t)m[3][2], (other_t)m[3][3]
    };
}

/*-------------------------------------
    Subscripting Operators
-------------------------------------*/
template <typename num_t>
inline const vec4_t<num_t>& mat4_t<num_t>::operator[](int i) const {
    return m[i];
}

template <typename num_t>
inline vec4_t<num_t>& mat4_t<num_t>::operator[](int i) {
    return m[i];
}

/*-------------------------------------
    Matrix-Matrix Operators
-------------------------------------*/
// prefix operators
template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator++ () {
    ++m[0][0]; ++m[0][1]; ++m[0][2]; ++m[0][3];
    ++m[1][0]; ++m[1][1]; ++m[1][2]; ++m[1][3];
    ++m[2][0]; ++m[2][1]; ++m[2][2]; ++m[2][3];
    ++m[3][0]; ++m[3][1]; ++m[3][2]; ++m[3][3];
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator-- () {
    --m[0][0]; --m[0][1]; --m[0][2]; --m[0][3];
    --m[1][0]; --m[1][1]; --m[1][2]; --m[1][3];
    --m[2][0]; --m[2][1]; --m[2][2]; --m[2][3];
    --m[3][0]; --m[3][1]; --m[3][2]; --m[3][3];
    return *this;
}

//postfix operators
template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator++ (int) {
    return mat4_t<num_t>{
        ++m[0][0], ++m[0][1], ++m[0][2], ++m[0][3],
        ++m[1][0], ++m[1][1], ++m[1][2], ++m[1][3],
        ++m[2][0], ++m[2][1], ++m[2][2], ++m[2][3],
        ++m[3][0], ++m[3][1], ++m[3][2], ++m[3][3]
    };
}

template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator-- (int) {
    return mat4_t<num_t>{
        --m[0][0], --m[0][1], --m[0][2], --m[0][3],
        --m[1][0], --m[1][1], --m[1][2], --m[1][3],
        --m[2][0], --m[2][1], --m[2][2], --m[2][3],
        --m[3][0], --m[3][1], --m[3][2], --m[3][3]
    };
}

template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator + (const mat4_t<num_t>& input) const {
    return mat4_t<num_t>{
        m[0][0] + input.m[0][0], m[0][1] + input.m[0][1], m[0][2] + input.m[0][2], m[0][3] + input.m[0][3],
        m[1][0] + input.m[1][0], m[1][1] + input.m[1][1], m[1][2] + input.m[1][2], m[1][3] + input.m[1][3],
        m[2][0] + input.m[2][0], m[2][1] + input.m[2][1], m[2][2] + input.m[2][2], m[2][3] + input.m[2][3],
        m[3][0] + input.m[3][0], m[3][1] + input.m[3][1], m[3][2] + input.m[3][2], m[3][3] + input.m[3][3]
    };
}

template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator - (const mat4_t<num_t>& input) const {
    return mat4_t<num_t>{
        m[0][0] - input.m[0][0], m[0][1] - input.m[0][1], m[0][2] - input.m[0][2], m[0][3] - input.m[0][3],
        m[1][0] - input.m[1][0], m[1][1] - input.m[1][1], m[1][2] - input.m[1][2], m[1][3] - input.m[1][3],
        m[2][0] - input.m[2][0], m[2][1] - input.m[2][1], m[2][2] - input.m[2][2], m[2][3] - input.m[2][3],
        m[3][0] - input.m[3][0], m[3][1] - input.m[3][1], m[3][2] - input.m[3][2], m[3][3] - input.m[3][3]
    };
}

//for operations like "matrix4a = -matrix4b"
template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator - () const {
    return mat4_t<num_t>{
        -m[0][0], -m[0][1], -m[0][2], -m[0][3],
        -m[1][0], -m[1][1], -m[1][2], -m[1][3],
        -m[2][0], -m[2][1], -m[2][2], -m[2][3],
        -m[3][0], -m[3][1], -m[3][2], -m[3][3]
    };
}

template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator * (const mat4_t<num_t>& input) const {
    const vec4_t<num_t>* n = input.m;
    return mat4_t<num_t>{
    //X
        (n[0][0]*m[0][0]) + (n[0][1]*m[1][0]) + (n[0][2]*m[2][0]) + (n[0][3]*m[3][0]),
        (n[0][0]*m[0][1]) + (n[0][1]*m[1][1]) + (n[0][2]*m[2][1]) + (n[0][3]*m[3][1]),
        (n[0][0]*m[0][2]) + (n[0][1]*m[1][2]) + (n[0][2]*m[2][2]) + (n[0][3]*m[3][2]),
        (n[0][0]*m[0][3]) + (n[0][1]*m[1][3]) + (n[0][2]*m[2][3]) + (n[0][3]*m[3][3]),
    //Y
        (n[1][0]*m[0][0]) + (n[1][1]*m[1][0]) + (n[1][2]*m[2][0]) + (n[1][3]*m[3][0]),
        (n[1][0]*m[0][1]) + (n[1][1]*m[1][1]) + (n[1][2]*m[2][1]) + (n[1][3]*m[3][1]),
        (n[1][0]*m[0][2]) + (n[1][1]*m[1][2]) + (n[1][2]*m[2][2]) + (n[1][3]*m[3][2]),
        (n[1][0]*m[0][3]) + (n[1][1]*m[1][3]) + (n[1][2]*m[2][3]) + (n[1][3]*m[3][3]),
    //Z
        (n[2][0]*m[0][0]) + (n[2][1]*m[1][0]) + (n[2][2]*m[2][0]) + (n[2][3]*m[3][0]),
        (n[2][0]*m[0][1]) + (n[2][1]*m[1][1]) + (n[2][2]*m[2][1]) + (n[2][3]*m[3][1]),
        (n[2][0]*m[0][2]) + (n[2][1]*m[1][2]) + (n[2][2]*m[2][2]) + (n[2][3]*m[3][2]),
        (n[2][0]*m[0][3]) + (n[2][1]*m[1][3]) + (n[2][2]*m[2][3]) + (n[2][3]*m[3][3]),
    //W
        (n[3][0]*m[0][0]) + (n[3][1]*m[1][0]) + (n[3][2]*m[2][0]) + (n[3][3]*m[3][0]),
        (n[3][0]*m[0][1]) + (n[3][1]*m[1][1]) + (n[3][2]*m[2][1]) + (n[3][3]*m[3][1]),
        (n[3][0]*m[0][2]) + (n[3][1]*m[1][2]) + (n[3][2]*m[2][2]) + (n[3][3]*m[3][2]),
        (n[3][0]*m[0][3]) + (n[3][1]*m[1][3]) + (n[3][2]*m[2][3]) + (n[3][3]*m[3][3])
    };
    // I really hope this is correct
}

template <typename num_t>
mat4_t<num_t>& mat4_t<num_t>::operator =(const mat4_t<num_t>& input) {
    m[0][0] = input.m[0][0];
    m[0][1] = input.m[0][1];
    m[0][2] = input.m[0][2];
    m[0][3] = input.m[0][3];
    
    m[1][0] = input.m[1][0];
    m[1][1] = input.m[1][1];
    m[1][2] = input.m[1][2];
    m[1][3] = input.m[1][3];
    
    m[2][0] = input.m[2][0];
    m[2][1] = input.m[2][1];
    m[2][2] = input.m[2][2];
    m[2][3] = input.m[2][3];
    
    m[3][0] = input.m[3][0];
    m[3][1] = input.m[3][1];
    m[3][2] = input.m[3][2];
    m[3][3] = input.m[3][3];
    
    return *this;
}

template <typename num_t>
mat4_t<num_t>& mat4_t<num_t>::operator =(mat4_t<num_t>&& input) {
    m[0][0] = input.m[0][0];
    m[0][1] = input.m[0][1];
    m[0][2] = input.m[0][2];
    m[0][3] = input.m[0][3];
    
    m[1][0] = input.m[1][0];
    m[1][1] = input.m[1][1];
    m[1][2] = input.m[1][2];
    m[1][3] = input.m[1][3];
    
    m[2][0] = input.m[2][0];
    m[2][1] = input.m[2][1];
    m[2][2] = input.m[2][2];
    m[2][3] = input.m[2][3];
    
    m[3][0] = input.m[3][0];
    m[3][1] = input.m[3][1];
    m[3][2] = input.m[3][2];
    m[3][3] = input.m[3][3];
    
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator += (const mat4_t<num_t>& input) {
    m[0][0] += input.m[0][0]; m[0][1] += input.m[0][1]; m[0][2] += input.m[0][2]; m[0][3] += input.m[0][3];
    m[1][0] += input.m[1][0]; m[1][1] += input.m[1][1]; m[1][2] += input.m[1][2]; m[1][3] += input.m[1][3];
    m[2][0] += input.m[2][0]; m[2][1] += input.m[2][1]; m[2][2] += input.m[2][2]; m[2][3] += input.m[2][3];
    m[3][0] += input.m[3][0]; m[3][1] += input.m[3][1]; m[3][2] += input.m[3][2]; m[3][3] += input.m[3][3];
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator -= (const mat4_t<num_t>& input) {
    m[0][0] -= input.m[0][0]; m[0][1] -= input.m[0][1]; m[0][2] -= input.m[0][2]; m[0][3] -= input.m[0][3];
    m[1][0] -= input.m[1][0]; m[1][1] -= input.m[1][1]; m[1][2] -= input.m[1][2]; m[1][3] -= input.m[1][3];
    m[2][0] -= input.m[2][0]; m[2][1] -= input.m[2][1]; m[2][2] -= input.m[2][2]; m[2][3] -= input.m[2][3];
    m[3][0] -= input.m[3][0]; m[3][1] -= input.m[3][1]; m[3][2] -= input.m[3][2]; m[3][3] -= input.m[3][3];
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator *= (const mat4_t<num_t>& input) {
    return *this = *this * input;
}

template <typename num_t> inline
bool mat4_t<num_t>::operator == (const mat4_t<num_t>& compare) const {
    return
        m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] && m[0][2] == compare.m[0][2] && m[0][3] == compare.m[0][3] &&
        m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1] && m[1][2] == compare.m[1][2] && m[1][3] == compare.m[1][3] &&
        m[2][0] == compare.m[2][0] && m[2][1] == compare.m[2][1] && m[2][2] == compare.m[2][2] && m[2][3] == compare.m[2][3] &&
        m[3][0] == compare.m[3][0] && m[3][1] == compare.m[3][1] && m[3][2] == compare.m[3][2] && m[3][3] == compare.m[3][3];
}

template <typename num_t> inline
bool mat4_t<num_t>::operator != (const mat4_t<num_t>& compare) const {
    return
        m[0][0] != compare.m[0][0] || m[0][1] != compare.m[0][1] || m[0][2] != compare.m[0][2] || m[0][3] != compare.m[0][3] ||
        m[1][0] != compare.m[1][0] || m[1][1] != compare.m[1][1] || m[1][2] != compare.m[1][2] || m[1][3] != compare.m[1][3] ||
        m[2][0] != compare.m[2][0] || m[2][1] != compare.m[2][1] || m[2][2] != compare.m[2][2] || m[2][3] != compare.m[2][3] ||
        m[3][0] != compare.m[3][0] || m[3][1] != compare.m[3][1] || m[3][2] != compare.m[3][2] || m[3][3] != compare.m[3][3];
}

/*-------------------------------------
    Vector-Matrix Math Operations (Declared in the 4D Vector header)
-------------------------------------*/
template <typename num_t> inline
mat4_t<num_t> vec4_t<num_t>::operator + (const mat4_t<num_t>& m) const {
    return mat4_t<num_t>{
        v[0] + m.m[0][0], v[0] + m.m[0][1], v[0] + m.m[0][2], v[0] + m.m[0][3],
        v[1] + m.m[1][0], v[1] + m.m[1][1], v[1] + m.m[1][2], v[1] + m.m[1][3],
        v[2] + m.m[2][0], v[2] + m.m[2][1], v[2] + m.m[2][2], v[2] + m.m[2][3],
        v[3] + m.m[3][0], v[3] + m.m[3][1], v[3] + m.m[3][2], v[3] + m.m[3][3]
    };
}

template <typename num_t> inline
mat4_t<num_t> vec4_t<num_t>::operator - (const mat4_t<num_t>& m) const {
    return mat4_t<num_t>{
        v[0] - m.m[0][0], v[0] - m.m[0][1], v[0] - m.m[0][2], v[0] - m.m[0][3],
        v[1] - m.m[1][0], v[1] - m.m[1][1], v[1] - m.m[1][2], v[1] - m.m[1][3],
        v[2] - m.m[2][0], v[2] - m.m[2][1], v[2] - m.m[2][2], v[2] - m.m[2][3],
        v[3] - m.m[3][0], v[3] - m.m[3][1], v[3] - m.m[3][2], v[3] - m.m[3][3]
    };
}

// Multiplies by a row vector
template <typename num_t> inline
vec4_t<num_t> vec4_t<num_t>::operator * (const mat4_t<num_t>& m) const {
    return vec4_t<num_t>{
        (m.m[0][0] * v[0]) + (m.m[1][0] * v[1]) + (m.m[2][0] * v[2]) + (m.m[3][0] * v[3]),
        (m.m[0][1] * v[0]) + (m.m[1][1] * v[1]) + (m.m[2][1] * v[2]) + (m.m[3][1] * v[3]),
        (m.m[0][2] * v[0]) + (m.m[1][2] * v[1]) + (m.m[2][2] * v[2]) + (m.m[3][2] * v[3]),
        (m.m[0][3] * v[0]) + (m.m[1][3] * v[1]) + (m.m[2][3] * v[2]) + (m.m[3][3] * v[3])
    };
}

template <typename num_t> inline
vec4_t<num_t>& vec4_t<num_t>::operator *= (const mat4_t<num_t>& m) {
    *this = *this * m;
    return *this;
}

/*-------------------------------------
    Matrix-Vector Operators
-------------------------------------*/
template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator + (const vec4_t<num_t>& input) const {
    return mat4_t{
        m[0][0] + input.v[0], m[0][1] + input.v[1], m[0][2] + input.v[2], m[0][3] + input.v[3],
        m[1][0] + input.v[0], m[1][1] + input.v[1], m[1][2] + input.v[2], m[1][3] + input.v[3],
        m[2][0] + input.v[0], m[2][1] + input.v[1], m[2][2] + input.v[2], m[2][3] + input.v[3],
        m[3][0] + input.v[0], m[3][1] + input.v[1], m[3][2] + input.v[2], m[3][3] + input.v[3]
    };
}

template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator - (const vec4_t<num_t>& input) const {
    return mat4_t{
        m[0][0] - input.v[0], m[0][1] - input.v[1], m[0][2] - input.v[2], m[0][3] - input.v[3],
        m[1][0] - input.v[0], m[1][1] - input.v[1], m[1][2] - input.v[2], m[1][3] - input.v[3],
        m[2][0] - input.v[0], m[2][1] - input.v[1], m[2][2] - input.v[2], m[2][3] - input.v[3],
        m[3][0] - input.v[0], m[3][1] - input.v[1], m[3][2] - input.v[2], m[3][3] - input.v[3]
    };
}

// Multiply by a column-vector
template <typename num_t> inline
vec4_t<num_t> mat4_t<num_t>::operator * (const vec4_t<num_t>& inVect) const {
    return vec4_t<num_t>{
        (m[0][0] * inVect.v[0]) + (m[0][1] * inVect.v[1]) + (m[0][2] * inVect.v[2]) + (m[0][3] * inVect.v[3]),
        (m[1][0] * inVect.v[0]) + (m[1][1] * inVect.v[1]) + (m[1][2] * inVect.v[2]) + (m[1][3] * inVect.v[3]),
        (m[2][0] * inVect.v[0]) + (m[2][1] * inVect.v[1]) + (m[2][2] * inVect.v[2]) + (m[2][3] * inVect.v[3]),
        (m[3][0] * inVect.v[0]) + (m[3][1] * inVect.v[1]) + (m[3][2] * inVect.v[2]) + (m[3][3] * inVect.v[3])
    };
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator = (const vec4_t<num_t>& input) {
    m[0][0] = input.v[0]; m[0][1] = input.v[1]; m[0][2] = input.v[2]; m[0][3] = input.v[3];
    m[1][0] = input.v[0]; m[1][1] = input.v[1]; m[1][2] = input.v[2]; m[1][3] = input.v[3];
    m[2][0] = input.v[0]; m[2][1] = input.v[1]; m[2][2] = input.v[2]; m[2][3] = input.v[3];
    m[3][0] = input.v[0]; m[3][1] = input.v[1]; m[3][2] = input.v[2]; m[3][3] = input.v[3];
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator += (const vec4_t<num_t>& input) {
    m[0][0] += input.v[0]; m[0][1] += input.v[1]; m[0][2] += input.v[2]; m[0][3] += input.v[3];
    m[1][0] += input.v[0]; m[1][1] += input.v[1]; m[1][2] += input.v[2]; m[1][3] += input.v[3];
    m[2][0] += input.v[0]; m[2][1] += input.v[1]; m[2][2] += input.v[2]; m[2][3] += input.v[3];
    m[3][0] += input.v[0]; m[3][1] += input.v[1]; m[3][2] += input.v[2]; m[3][3] += input.v[3];
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator -= (const vec4_t<num_t>& input) {
    m[0][0] -= input.v[0]; m[0][1] -= input.v[1]; m[0][2] -= input.v[2]; m[0][3] -= input.v[3];
    m[1][0] -= input.v[0]; m[1][1] -= input.v[1]; m[1][2] -= input.v[2]; m[1][3] -= input.v[3];
    m[2][0] -= input.v[0]; m[2][1] -= input.v[1]; m[2][2] -= input.v[2]; m[2][3] -= input.v[3];
    m[3][0] -= input.v[0]; m[3][1] -= input.v[1]; m[3][2] -= input.v[2]; m[3][3] -= input.v[3];
    return *this;
}

/*-------------------------------------
    Matrix-Scalar Operators
-------------------------------------*/
template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator + (num_t input) const {
    return mat4_t<num_t>{
        m[0][0] + input, m[0][1] + input, m[0][2] + input, m[0][3] + input,
        m[1][0] + input, m[1][1] + input, m[1][2] + input, m[1][3] + input,
        m[2][0] + input, m[2][1] + input, m[2][2] + input, m[2][3] + input,
        m[3][0] + input, m[3][1] + input, m[3][2] + input, m[3][3] + input
    };
}

template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator - (num_t input) const {
    return mat4_t<num_t>{
        m[0][0] - input, m[0][1] - input, m[0][2] - input, m[0][3] - input,
        m[1][0] - input, m[1][1] - input, m[1][2] - input, m[1][3] - input,
        m[2][0] - input, m[2][1] - input, m[2][2] - input, m[2][3] - input,
        m[3][0] - input, m[3][1] - input, m[3][2] - input, m[3][3] - input
    };
}

template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator * (num_t input) const {
    return mat4_t<num_t>{
        m[0][0] * input, m[0][1] * input, m[0][2] * input, m[0][3] * input,
        m[1][0] * input, m[1][1] * input, m[1][2] * input, m[1][3] * input,
        m[2][0] * input, m[2][1] * input, m[2][2] * input, m[2][3] * input,
        m[3][0] * input, m[3][1] * input, m[3][2] * input, m[3][3] * input
    };
}

template <typename num_t> inline
mat4_t<num_t> mat4_t<num_t>::operator / (num_t input) const {
    return mat4_t<num_t>{
        m[0][0] / input, m[0][1] / input, m[0][2] / input, m[0][3] / input,
        m[1][0] / input, m[1][1] / input, m[1][2] / input, m[1][3] / input,
        m[2][0] / input, m[2][1] / input, m[2][2] / input, m[2][3] / input,
        m[3][0] / input, m[3][1] / input, m[3][2] / input, m[3][3] / input
    };
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator = (num_t input) {
    m[0][0] = input; m[0][1] = input; m[0][2] = input; m[0][3] = input;
    m[1][0] = input; m[1][1] = input; m[1][2] = input; m[1][3] = input;
    m[2][0] = input; m[2][1] = input; m[2][2] = input; m[2][3] = input;
    m[3][0] = input; m[3][1] = input; m[3][2] = input; m[3][3] = input;
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator += (num_t input) {
    m[0][0] += input; m[0][1] += input; m[0][2] += input; m[0][3] += input;
    m[1][0] += input; m[1][1] += input; m[1][2] += input; m[1][3] += input;
    m[2][0] += input; m[2][1] += input; m[2][2] += input; m[2][3] += input;
    m[3][0] += input; m[3][1] += input; m[3][2] += input; m[3][3] += input;
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator -= (num_t input) {
    m[0][0] -= input; m[0][1] -= input; m[0][2] -= input; m[0][3] -= input;
    m[1][0] -= input; m[1][1] -= input; m[1][2] -= input; m[1][3] -= input;
    m[2][0] -= input; m[2][1] -= input; m[2][2] -= input; m[2][3] -= input;
    m[3][0] -= input; m[3][1] -= input; m[3][2] -= input; m[3][3] -= input;
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator *= (num_t input) {
    m[0][0] *= input; m[0][1] *= input; m[0][2] *= input; m[0][3] *= input;
    m[1][0] *= input; m[1][1] *= input; m[1][2] *= input; m[1][3] *= input;
    m[2][0] *= input; m[2][1] *= input; m[2][2] *= input; m[2][3] *= input;
    m[3][0] *= input; m[3][1] *= input; m[3][2] *= input; m[3][3] *= input;
    return *this;
}

template <typename num_t> inline
mat4_t<num_t>& mat4_t<num_t>::operator /= (num_t input) {
    m[0][0] /= input; m[0][1] /= input; m[0][2] /= input; m[0][3] /= input;
    m[1][0] /= input; m[1][1] /= input; m[1][2] /= input; m[1][3] /= input;
    m[2][0] /= input; m[2][1] /= input; m[2][2] /= input; m[2][3] /= input;
    m[3][0] /= input; m[3][1] /= input; m[3][2] /= input; m[3][3] /= input;
    return *this;
}

/*-------------------------------------
    Non-Member Matrix-Scalar operations
-------------------------------------*/
template <typename num_t> inline
mat4_t<num_t> operator + (num_t n, const mat4_t<num_t>& m) {
    return m + n;
}

template <typename num_t> inline
mat4_t<num_t> operator - (num_t n, const mat4_t<num_t>& m) {
    return m - n;
}

template <typename num_t> inline
mat4_t<num_t> operator * (num_t n, const mat4_t<num_t>& m) {
    return m * n;
}

} //end math namespace
} //end ls namespace
