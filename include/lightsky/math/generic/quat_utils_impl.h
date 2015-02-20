
namespace ls {

/*-----------------------------------------------------------------------------
    Quaternion Functions
-----------------------------------------------------------------------------*/
/*-------------------------------------
    dot
-------------------------------------*/
template <typename num_t> constexpr
num_t math::dot(const quat_t<num_t>& q1, const quat_t<num_t>& q2) {
    return (q1.q[0] * q2.q[0]) + (q1.q[1] * q2.q[1]) + (q1.q[2] * q2.q[2]) + (q1.q[3] * q2.q[3]);
}

/*-------------------------------------
    lengthSquared
-------------------------------------*/
template <typename num_t> constexpr
num_t math::lengthSquared(const quat_t<num_t>& q) {
    return (q.q[0]*q.q[0]) + (q.q[1]*q.q[1]) + (q.q[2]*q.q[2]) + (q.q[3]*q.q[3]);
}

/*-------------------------------------
    length
-------------------------------------*/
template <typename num_t> inline
num_t math::length(const quat_t<num_t>& q) {
    return (num_t) LS_SQRT(lengthSquared<num_t>(q));
}

/*-------------------------------------
    inverse
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::inverse(const quat_t<num_t>& q) {
    const num_t magInv{fastInvSqrt<num_t>(lengthSquared<num_t>(q))};
    return quat_t<num_t>{
        -q.q[0] * magInv,
        -q.q[1] * magInv,
        -q.q[2] * magInv,
        q.q[3] * magInv
    };
}

/*-------------------------------------
    conjugate
-------------------------------------*/
template <typename num_t> constexpr
math::quat_t<num_t> math::conjugate(const quat_t<num_t>& q) {
    return quat_t<num_t>{-q.q[0], -q.q[1], -q.q[2], q.q[3]};
}

/*-------------------------------------
    normalize
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::normalize(const quat_t<num_t>& q) {
    const num_t magInv{fastInvSqrt<num_t>(lengthSquared<num_t>(q))};
    
    return quat_t<num_t>{
        q.q[0] * magInv,
        q.q[1] * magInv,
        q.q[2] * magInv,
        q.q[3] * magInv
    };
}

/*-------------------------------------
    Vector rotation using a Quaternion
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::rotate(const vec3_t<num_t>& v, const quat_t<num_t>& q) {
    const vec3_t<num_t> qVec = {q[0], q[1], q[2]};
    const vec3_t<num_t> qCrossV = cross<num_t>(qVec, v);
    const num_t         qReal   = q[3];
    const num_t         qDotV   = dot<num_t>(qVec, v);
    const num_t         qLenSq  = lengthSquared<num_t>(qVec);
    
    return vec3_t<num_t>{
        num_t{2} * qDotV * qVec
        + (qReal*qReal - qLenSq) * v
        + num_t{2} * qReal * qCrossV
    };
}

/*-------------------------------------
    lerp
-------------------------------------*/
template <typename num_t> constexpr
math::quat_t<num_t> math::lerp(const quat_t<num_t>& q1, const quat_t<num_t>& q2, num_t percent) {
    return quat_t<num_t>{q1 + ((q2 - q1) * percent)};
}

/*-------------------------------------
    nlerp
-------------------------------------*/
template <typename num_t> constexpr
math::quat_t<num_t> math::nlerp(const quat_t<num_t>& q1, const quat_t<num_t>& q2, num_t percent) {
    return normalize(lerp<num_t>(q1, q2, percent));
}

/*-------------------------------------
    slerp
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::slerp(const quat_t<num_t>& q1, const quat_t<num_t>& q2, num_t t) {
    num_t dotProd = dot(q1, q2);

    // Reverse the sign of q2 if q1.q2 < 0.
    if (dotProd < num_t{0}) {
        dotProd = -dotProd;
    }

    const num_t theta = acos(dotProd);
    num_t mult1, mult2;

    if (theta >= LS_EPSILON) {
        const num_t st = (num_t) LS_SIN(theta);
        mult1 = LS_SIN((num_t{1} - t) * theta) / st;
        mult2 = LS_SIN(t * theta) / st;
    }
    else {
        // To avoid division by 0 and by very small numbers the approximation of sin(angle)
        // by angle is used when theta is small (0.000001 is chosen arbitrarily).
        mult1 = num_t{1} - t;
        mult2 = t;
    }

    return quat_t<num_t>{
        mult1 * q1.q[0] + mult2 * q2.q[0],
        mult1 * q1.q[1] + mult2 * q2.q[1],
        mult1 * q1.q[2] + mult2 * q2.q[2],
        mult1 * q1.q[3] + mult2 * q2.q[3]
    };
}

/*-------------------------------------
    lookAt
-------------------------------------*/
template <typename num_t>
math::quat_t<num_t> math::lookAt(const math::vec3_t<num_t>& target, const math::vec3_t<num_t>& dir){
    const vec3_t<num_t>&& a = normalize<num_t>(target);
    const vec3_t<num_t>&& b = normalize<num_t>(dir);
    
    const vec3_t<num_t>&& w = cross<num_t>(a, b);
    
    const quat_t<num_t>&& q{w[0], w[1], w[2], num_t{1} + dot<num_t>(a, b)};
    
    return normalize<num_t>(q);
}

/*-----------------------------------------------------------------------------
    Quaternions & Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    quatToMat3
-------------------------------------*/
template <typename num_t> inline
math::mat3_t<num_t> math::quatToMat3(const quat_t<num_t>& q) {
    const num_t xx = q.q[0] * q.q[0] * num_t{2};
    const num_t yy = q.q[1] * q.q[1] * num_t{2};
    const num_t zz = q.q[2] * q.q[2] * num_t{2};
    const num_t xy = q.q[0] * q.q[1];
    const num_t xz = q.q[0] * q.q[2];
    const num_t xw = q.q[0] * q.q[3];
    const num_t yz = q.q[1] * q.q[2];
    const num_t yw = q.q[1] * q.q[3];
    const num_t zw = q.q[2] * q.q[3];

    return mat3_t<num_t>{
        num_t{1}-(yy + zz),   num_t{2}*(xy + zw),   num_t{2}*(xz - yw),
        num_t{2}*(xy - zw),   num_t{1}-(xx + zz),   num_t{2}*(yz + xw),
        num_t{2}*(xz + yw),   num_t{2}*(yz - xw),   num_t{1}-(xx + yy)
    };
}

/*-------------------------------------
    quatToMat4
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::quatToMat4(const quat_t<num_t>& q) {
    const num_t xx = q.q[0] * q.q[0] * num_t{2};
    const num_t yy = q.q[1] * q.q[1] * num_t{2};
    const num_t zz = q.q[2] * q.q[2] * num_t{2};
    const num_t xy = q.q[0] * q.q[1];
    const num_t xz = q.q[0] * q.q[2];
    const num_t xw = q.q[0] * q.q[3];
    const num_t yz = q.q[1] * q.q[2];
    const num_t yw = q.q[1] * q.q[3];
    const num_t zw = q.q[2] * q.q[3];

    return mat4_t<num_t>{
        num_t{1}-(yy + zz),   num_t{2}*(xy + zw),   num_t{2}*(xz - yw),   num_t{0},
        num_t{2}*(xy - zw),   num_t{1}-(xx + zz),   num_t{2}*(yz + xw),   num_t{0},
        num_t{2}*(xz + yw),   num_t{2}*(yz - xw),   num_t{1}-(xx + yy),   num_t{0},
        num_t{0},             num_t{0},             num_t{0},             num_t{1}
    };
}

/*-------------------------------------
    matToQuat
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::matToQuat(const mat3_t<num_t>& m) {
    num_t s(0);
    num_t trace(m.m[0][0] + m.m[1][1] + m.m[2][2]);
    quat_t<num_t> q;

    if (trace > num_t{0}) {
        s = LS_SQRT(trace + num_t{1});
        q.q[3] = s * num_t{0.5};
        s = num_t{0.5} / s;
        q.q[0] = (m.m[1][2] - m.m[2][1]) * s;
        q.q[1] = (m.m[2][0] - m.m[0][2]) * s;
        q.q[2] = (m.m[0][1] - m.m[1][0]) * s;
    }
    else {
        int nxt[3] = {1, 2, 0};
        int i(0), j(0), k(0);

        if (m.m[1][1] > m.m[0][0]) {
            i = 1;
        }

        if (m.m[2][2] > m.m[i][i]) {
            i = 2;
        }

        j = nxt[i];
        k = nxt[j];
        s = LS_SQRT((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + num_t{1});

        q[i] = s * num_t{0.5};
        s = num_t{0.5} / s;
        q[3] = (m.m[j][k] - m.m[k][j]) * s;
        q[j] = (m.m[i][j] + m.m[j][i]) * s;
        q[k] = (m.m[i][k] + m.m[k][i]) * s;
    }
    
    return q;
}

/*-------------------------------------
    matToQuat
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::matToQuat(const mat4_t<num_t>& m) {
    num_t s(0);
    num_t trace(m.m[0][0] + m.m[1][1] + m.m[2][2]);
    quat_t<num_t> q;

    if (trace > num_t{0}) {
        s = LS_SQRT(trace + num_t{1});
        q.q[3] = s * num_t{0.5};
        s = num_t{0.5} / s;
        q.q[0] = (m.m[1][2] - m.m[2][1]) * s;
        q.q[1] = (m.m[2][0] - m.m[0][2]) * s;
        q.q[2] = (m.m[0][1] - m.m[1][0]) * s;
    }
    else {
        int nxt[3] = {1, 2, 0};
        int i(0), j(0), k(0);

        if (m.m[1][1] > m.m[0][0]) {
            i = 1;
        }

        if (m.m[2][2] > m.m[i][i]) {
            i = 2;
        }

        j = nxt[i];
        k = nxt[j];
        s = LS_SQRT((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + num_t{1});

        q[i] = s * num_t{0.5};
        s = num_t{0.5} / s;
        q[3] = (m.m[j][k] - m.m[k][j]) * s;
        q[j] = (m.m[i][j] + m.m[j][i]) * s;
        q[k] = (m.m[i][k] + m.m[k][i]) * s;
    }
    return q;
}

/*-----------------------------------------------------------------------------
    Quaternions & Euler Angles
-----------------------------------------------------------------------------*/
/*
 * Methods to extract quaternion components was found here:
 * http://nic-gamedev.blogspot.com/2011/11/quaternion-math-getting-local-axis.html
 * 
 * The equations for these functions can also be found in the quatToMatN() functions.
 */
/*-------------------------------------
    getAxisX
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::getAxisX(const math::quat_t<num_t>& q) {
    return math::vec3_t<num_t>{
        num_t{1} - num_t{2} * (q[1] * q[1] + q[2] * q[2]),
        num_t{2} * (q[0] * q[1] + q[3] * q[2]),
        num_t{2} * (q[0] * q[2] - q[3] * q[1])
    };
}

/*-------------------------------------
    getAxisY
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::getAxisY(const math::quat_t<num_t>& q) {
    return math::vec3_t<num_t>{
        num_t{2} * (q[0] * q[1] - q[3] * q[2]),
        num_t{1} - num_t{2} * (q[0] * q[0] + q[2] * q[2]),
        num_t{2} * (q[1] * q[2] + q[3] * q[0])
    };
}

/*-------------------------------------
    getAxisZ
-------------------------------------*/
template <typename num_t> constexpr
math::vec3_t<num_t> math::getAxisZ(const math::quat_t<num_t>& q) {
    return math::vec3_t<num_t>{
        num_t{2} * (q[0] * q[2] + q[3] * q[1]),
        num_t{2} * (q[1] * q[2] - q[3] * q[0]),
        num_t{1} - num_t{2} * (q[0] * q[0] + q[1] * q[1])
    };
}

/*-------------------------------------
    getAngle
-------------------------------------*/
template <typename num_t> inline
num_t math::getAngle(const quat_t<num_t>& q) {
    return num_t{std::acos(q.q[3] * num_t{2})};
}

/*-------------------------------------
    toEuler
-------------------------------------*/
template <typename num_t> inline
math::vec3_t<num_t> math::toEuler(const quat_t<num_t>& q) {
    const num_t xx = q.q[0] * q.q[0];
    const num_t yy = q.q[1] * q.q[1];
    const num_t zz = q.q[2] * q.q[2];
    
    const num_t pitch = std::atan2(
        num_t{2} * ((q.q[3] * q.q[0]) * (q.q[1] * q.q[2])),
        num_t{1} - (num_t{2} * (xx + yy))
    );
    const num_t yaw = std::asin(num_t{2} * ((q.q[3] * q.q[1]) - (q.q[2] * q.q[0])));
    const num_t roll = std::atan2(
        num_t{2} * ((q.q[3] * q.q[2]) + (q.q[0] * q.q[1])),
        num_t{1} - (num_t{2} * (yy + zz))
    );
    
    return vec3_t<num_t>{pitch, yaw, roll};
}

/*-------------------------------------
    fromEuler
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::fromEuler(const math::vec3_t<num_t>& angles) {
    const num_t cp = LS_COS(angles.v[0] * num_t{0.5});
    const num_t sp = LS_SIN(angles.v[0] * num_t{0.5});

    const num_t cy = LS_COS(angles.v[1] * num_t{0.5});
    const num_t sy = LS_SIN(angles.v[1] * num_t{0.5});

    const num_t cr = LS_COS(angles.v[2] * num_t{0.5});
    const num_t sr = LS_SIN(angles.v[2] * num_t{0.5});

    return math::quat_t<num_t>{
        (sy * cp * cr) - (cy * sp * sr),
        (cy * sp * cr) + (sy * cp * sr),
        (cy * cp * sr) - (sy * sp * cr),
        (cy * cp * cr) + (sy * sp * sr)
    };
}

/*-------------------------------------
    fromEuler
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::fromEuler(num_t pitch, num_t yaw, num_t roll) {
    const num_t cp = LS_COS(pitch * num_t{0.5});
    const num_t sp = LS_SIN(pitch * num_t{0.5});

    const num_t cy = LS_COS(yaw * num_t{0.5});
    const num_t sy = LS_SIN(yaw * num_t{0.5});

    const num_t cr = LS_COS(roll * num_t{0.5});
    const num_t sr = LS_SIN(roll * num_t{0.5});

    return math::quat_t<num_t>{
        (sy * cp * cr) - (cy * sp * sr),
        (cy * sp * cr) + (sy * cp * sr),
        (cy * cp * sr) - (sy * sp * cr),
        (cy * cp * cr) + (sy * sp * sr)
    };
}

/*-------------------------------------
    toAxisAngle
-------------------------------------*/
template <typename num_t> inline
void math::toAxisAngle(const quat_t<num_t>& q, vec3_t<num_t>& outAxis, num_t& outAngle) {
    num_t s = LS_SQRT(num_t{1} - (q.q[3] * q.q[3]));

    if (std::abs(s) <= num_t{0}) {
        s = num_t{1};
    }
    else {
        s = num_t{1} / s;
    }

    outAxis.v[0] = q.q[0] * s,
    outAxis.v[1] = q.q[1] * s,
    outAxis.v[2] = q.q[2] * s,
    outAngle = std::acos(q.q[3]) * num_t{2};
}

/*-------------------------------------
    toAxisAngle
-------------------------------------*/
template <typename num_t> inline
math::vec4_t<num_t> math::toAxisAngle(const quat_t<num_t>& q) {
    const num_t c = q.q[3];
    num_t s = LS_SQRT(num_t{1} - c * c);

    if (std::abs(s) <= num_t{0}) {
        s = num_t{1};
    }
    else {
        s = num_t{1} / s;
    }

    return vec4_t<num_t>(
        q.q[0] * s,
        q.q[1] * s,
        q.q[2] * s,
        std::acos(q.q[3]) * num_t{2}
    );
}

/*-------------------------------------
    fromAxisAngle
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::fromAxisAngle(const vec3_t<num_t>& axis, num_t angle) {
    num_t a = angle * num_t{0.5};
    num_t s = LS_SIN(a);
    
    return quat_t<num_t>{
        s * axis.v[0],
        s * axis.v[1],
        s * axis.v[2],
        LS_COS(a)
    };
}

/*-------------------------------------
    fromAxisAngle
-------------------------------------*/
template <typename num_t> inline
math::quat_t<num_t> math::fromAxisAngle(const vec4_t<num_t>& v) {
    num_t a = v.v[3] * num_t{0.5};
    num_t s = LS_SIN(a);
    return quat_t<num_t>{
        s * v.v[0],
        s * v.v[1],
        s * v.v[2],
        LS_COS(a)
    };
}

} // end ls namespace
