
namespace ls {
namespace math {

/*-------------------------------------
    Non-Member Quaternion-Scalar operations
-------------------------------------*/
template <typename num_t> inline
quat_t<num_t> operator + (num_t n, const quat_t<num_t>& q);

template <typename num_t> inline
quat_t<num_t> operator - (num_t n, const quat_t<num_t>& q);

template <typename num_t> inline
quat_t<num_t> operator * (num_t n, const quat_t<num_t>& q);

template <typename num_t> inline
quat_t<num_t> operator / (num_t n, const quat_t<num_t>& q);

/*-------------------------------------
    Constructors
-------------------------------------*/
// Main Constructor
template <typename num_t>
constexpr quat_t<num_t>::quat_t(num_t inX, num_t inY, num_t inZ, num_t inW) :
    q{inX, inY, inZ, inW}
{}

template <typename num_t>
constexpr quat_t<num_t>::quat_t() :
    q{num_t{0}, num_t{0}, num_t{0}, num_t{1}}
{}

template <typename num_t>
constexpr quat_t<num_t>::quat_t(num_t n) :
    q{n, n, n, num_t{1}}
{}

template <typename num_t>
constexpr quat_t<num_t>::quat_t(const quat_t<num_t>& q) :
    q{q.q[0], q.q[1], q.q[2],q.q[3]}
{}

template <typename num_t>
constexpr quat_t<num_t>::quat_t(quat_t<num_t>&& q) :
    q{q.q[0], q.q[1], q.q[2],q.q[3]}
{}

/*-------------------------------------
    Conversions & Casting
-------------------------------------*/
template <typename num_t>
template <typename other_t>
constexpr quat_t<num_t>::operator quat_t<other_t>() const {
    return quat_t<other_t>{
        (other_t)q[0], (other_t)q[1], (other_t)q[2], (other_t)q[3]
    };
}

template <typename num_t>
const num_t* quat_t<num_t>::operator&() const {
    return q;
}

template <typename num_t>
inline num_t* quat_t<num_t>::operator&() {
    return q;
}

/*-------------------------------------
    Subscripting Operators
-------------------------------------*/
template <typename num_t>
constexpr num_t quat_t<num_t>::operator[] (int i) const {
    return q[i];
}

template <typename num_t>
inline num_t& quat_t<num_t>::operator[] (int i) {
    return q[i];
}

/*-------------------------------------
    Quaternion-Quaternion Operators
-------------------------------------*/
// prefix operators
template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator++ () {
    ++q[0]; ++q[1]; ++q[2]; ++q[3];
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator-- () {
    --q[0]; --q[1]; --q[2]; --q[3];
    return *this;
}

//postfix operators
template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator++ (int) {
    return quat_t<num_t>{
        ++q[0], ++q[1], ++q[2], ++q[3]
    };
}

template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator-- (int) {
    return quat_t<num_t>{
        --q[0], --q[1], --q[2], --q[3]
    };
}

template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator + (const quat_t<num_t>& input) const {
    return quat_t<num_t>{
        q[0] + input.q[0],
        q[1] + input.q[1],
        q[2] + input.q[2],
        q[3] + input.q[3]
    };
}

template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator - (const quat_t<num_t>& input) const {
    return quat_t<num_t>{
        q[0] - input.q[0],
        q[1] - input.q[1],
        q[2] - input.q[2],
        q[3] - input.q[3]
    };
}

template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator * (const quat_t<num_t>& input) const {
    return quat_t<num_t>{
        (input.q[3]*q[0]) + (input.q[0]*q[3]) + (input.q[1]*q[2]) - (input.q[2]*q[1]),
        (input.q[3]*q[1]) - (input.q[0]*q[2]) + (input.q[1]*q[3]) + (input.q[2]*q[0]),
        (input.q[3]*q[2]) + (input.q[0]*q[1]) - (input.q[1]*q[0]) + (input.q[2]*q[3]),
        (input.q[3]*q[3]) - (input.q[0]*q[0]) - (input.q[1]*q[1]) - (input.q[2]*q[2])
    };
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator = (const quat_t<num_t>& input) {
    q[0] = input.q[0];
    q[1] = input.q[1];
    q[2] = input.q[2];
    q[3] = input.q[3];
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator = (quat_t<num_t>&& input) {
    q[0] = input.q[0];
    q[1] = input.q[1];
    q[2] = input.q[2];
    q[3] = input.q[3];
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator += (const quat_t<num_t>& input) {
    q[0] += input.q[0];
    q[1] += input.q[1];
    q[2] += input.q[2];
    q[3] += input.q[3];
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator -= (const quat_t<num_t>& input) {
    q[0] -= input.q[0];
    q[1] -= input.q[1];
    q[2] -= input.q[2];
    q[3] -= input.q[3];
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator *= (const quat_t<num_t>& input) {
    return *this = *this * input;
}

template <typename num_t> inline
bool quat_t<num_t>::operator == (const quat_t<num_t>& compare) const {
    return
        q[0] == compare.q[0] &&
        q[1] == compare.q[1] &&
        q[2] == compare.q[2] &&
        q[3] == compare.q[3];
}

template <typename num_t> inline
bool quat_t<num_t>::operator != (const quat_t<num_t>& compare) const {
    return
        q[0] != compare.q[0] ||
        q[1] != compare.q[1] ||
        q[2] != compare.q[2] ||
        q[3] != compare.q[3];
}

/*-------------------------------------
    Quaternion-Scalar Operators
-------------------------------------*/
template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator + (num_t input) const {
    return quat_t<num_t>{
        q[0] + input,
        q[1] + input,
        q[2] + input,
        q[3] + input
    };
}

template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator - (num_t input) const {
    return quat_t<num_t>{
        q[0] - input,
        q[1] - input,
        q[2] - input,
        q[3] - input
    };
}

template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator * (num_t input) const {
    return quat_t<num_t>{
        q[0] * input,
        q[1] * input,
        q[2] * input,
        q[3] * input
    };
}

template <typename num_t> inline
quat_t<num_t> quat_t<num_t>::operator / (num_t input) const {
    return quat_t<num_t>{
        q[0] / input,
        q[1] / input,
        q[2] / input,
        q[3] / input
    };
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator = (num_t input) {
    q[0] = input;
    q[1] = input;
    q[2] = input;
    q[3] = input;
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator += (num_t input) {
    q[0] += input;
    q[1] += input;
    q[2] += input;
    q[3] += input;
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator -= (num_t input) {
    q[0] -= input;
    q[1] -= input;
    q[2] -= input;
    q[3] -= input;
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator *= (num_t input) {
    q[0] *= input;
    q[1] *= input;
    q[2] *= input;
    q[3] *= input;
    return *this;
}

template <typename num_t> inline
quat_t<num_t>& quat_t<num_t>::operator /= (num_t input) {
    q[0] /= input;
    q[1] /= input;
    q[2] /= input;
    q[3] /= input;
    return *this;
}

/*-------------------------------------
    Non-Member Quaternion-Scalar operations
-------------------------------------*/
template <typename num_t> inline
quat_t<num_t> operator + (num_t n, const quat_t<num_t>& q) {
    return q + n;
}

template <typename num_t> inline
quat_t<num_t> operator - (num_t n, const quat_t<num_t>& q) {
    return q - n;
}

template <typename num_t> inline
quat_t<num_t> operator * (num_t n, const quat_t<num_t>& q) {
    return q * n;
}

template <typename num_t> inline
quat_t<num_t> operator / (num_t n, const quat_t<num_t>& q) {
    return q / n;
}

} //end math namespace
} //end ls namespace
