
namespace ls {

/*-----------------------------------------------------------------------------
    2x2 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    2x2 Determinant
-------------------------------------*/
template <typename num_t> constexpr
num_t math::determinant(const mat2_t<num_t>& m) {
    return (m.m[0][0] * m.m[1][1]) - (m.m[0][1] * m.m[1][0]);
}

/*-------------------------------------
    2x2 Transpose
-------------------------------------*/
template <typename num_t> constexpr
math::mat2_t<num_t> math::transpose(const mat2_t<num_t>& m) {
    return mat2_t<num_t>{
        m.m[0][0], m.m[1][0],
        m.m[0][1], m.m[1][1]
    };
}

/*-------------------------------------
    2x2 Inverse
-------------------------------------*/
template <typename num_t> constexpr
math::mat2_t<num_t> math::inverse(const mat2_t<num_t>& m) {
    return mat2_t<num_t>{
        m.m[1][1],  -m.m[0][1],
        -m.m[1][0], m.m[0][0]
    }
    *(num_t{1} / determinant(m));
}

/*-------------------------------------
    2x2 Rotation
-------------------------------------*/
template <typename num_t> inline
math::mat2_t<num_t> math::rotate(const mat2_t<num_t>& m, num_t angle) {
    const num_t c = LS_COS(angle);
    const num_t s = LS_SIN(angle);
    
    return m * mat2_t<num_t>{
        c,  s,
        -s, c
    };
}

/*-------------------------------------
    2x2 Scaling
-------------------------------------*/
template <typename num_t> constexpr
math::mat2_t<num_t> math::scale(const mat2_t<num_t>& m, const vec2_t<num_t>& amount) {
    return mat2_t<num_t>{
        m.m[0][0]*amount.v[0],  m.m[0][1],
        m.m[1][0],              m.m[1][1]*amount.v[1]
    };
}

/*-----------------------------------------------------------------------------
    3x3 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    3x3 Determinant
-------------------------------------*/
template <typename num_t> constexpr
num_t math::determinant(const mat3_t<num_t>& m) {
    return
        (m.m[0][0] * m.m[1][1] * m.m[2][2]) +
        (m.m[0][1] * m.m[1][2] * m.m[2][0]) +
        (m.m[0][2] * m.m[1][0] * m.m[2][1]) -
        (m.m[0][2] * m.m[1][1] * m.m[2][0]) -
        (m.m[0][1] * m.m[1][0] * m.m[2][2]) -
        (m.m[0][0] * m.m[1][2] * m.m[2][1]);
}

/*-------------------------------------
    3x3 Inverse
-------------------------------------*/
template <typename num_t> constexpr
math::mat3_t<num_t> math::inverse(const mat3_t<num_t>& m) {
    return mat3_t<num_t>{
        (m.m[1][1]*m.m[2][2] - m.m[2][1]*m.m[1][2]),
        (m.m[2][0]*m.m[1][2] - m.m[1][0]*m.m[2][2]),
        (m.m[1][0]*m.m[2][1] - m.m[2][0]*m.m[1][1]),
        (m.m[2][1]*m.m[0][2] - m.m[0][1]*m.m[2][2]),
        (m.m[0][0]*m.m[2][2] - m.m[2][0]*m.m[0][2]),
        (m.m[2][0]*m.m[0][1] - m.m[0][0]*m.m[2][1]),
        (m.m[0][1]*m.m[1][2] - m.m[1][1]*m.m[0][2]),
        (m.m[1][0]*m.m[0][2] - m.m[0][0]*m.m[1][2]),
        (m.m[0][0]*m.m[1][1] - m.m[1][0]*m.m[0][1])
    }
    *(num_t{1} / determinant(m));
}

/*-------------------------------------
    3x3 Transpose
-------------------------------------*/
template <typename num_t> constexpr
math::mat3_t<num_t> math::transpose(const mat3_t<num_t>& m) {
    return mat3_t<num_t>{
        m.m[0][0], m.m[1][0], m.m[2][0],
        m.m[0][1], m.m[1][1], m.m[2][1],
        m.m[0][2], m.m[1][2], m.m[2][2]
    };
}

/*-------------------------------------
    3x3 Rotation
-------------------------------------*/
template <typename num_t> inline
math::mat3_t<num_t> math::rotate(const mat3_t<num_t>& m, const vec3_t<num_t>& axis, num_t angle) {
    const num_t c           = LS_COS(angle);
    const num_t s           = LS_SIN(angle);
    const vec3_t<num_t>&& a = normalize<num_t>(axis);
    const num_t omc         = num_t{1} - c;
    const num_t xy          = (a.v[0] * a.v[1]) * omc;
    const num_t yz          = (a.v[1] * a.v[2]) * omc;
    const num_t zx          = (a.v[2] * a.v[0]) * omc;
    const num_t sx          = s * a.v[0];
    const num_t sy          = s * a.v[1];
    const num_t sz          = s * a.v[2];

    return m * mat3_t<num_t>{
        c + ((a.v[0] * a.v[0]) * omc),          xy + sz,                        zx - sy,
        xy - sz,                                c + ((a.v[1] * a.v[1]) * omc),  yz + sx,
        zx + sy,                                yz - sx,                        c + ((a.v[2] * a.v[2]) * omc)
    };
}

/*-------------------------------------
    3x3 Scaling
-------------------------------------*/
template <typename num_t> constexpr
math::mat3_t<num_t> math::scale(const mat3_t<num_t>& m, const vec3_t<num_t>& scale) {
    return mat3_t<num_t>{
        m.m[0][0]*scale.v[0],   m.m[0][1],              m.m[0][2],
        m.m[1][0],              m.m[1][1]*scale.v[1],   m.m[1][2],
        m.m[2][0],              m.m[2][1],              m.m[2][2]*scale.v[2]
    };
}

/*-------------------------------------
    3x3 Translation
-------------------------------------*/
template <typename num_t> constexpr
math::mat3_t<num_t> math::translate(const mat3_t<num_t>& m, const vec2_t<num_t>& t) {
    return mat3_t<num_t>{
        m.m[0][0],          m.m[0][1],          m.m[0][2],
        m.m[1][0],          m.m[1][1],          m.m[1][2],
        m.m[2][0]+t.v[0],   m.m[2][1]+t.v[1],   m.m[2][2]
    };
}

/*-----------------------------------------------------------------------------
    4x4 Matrices
-----------------------------------------------------------------------------*/
/*-------------------------------------
    4x4 Determinant
-------------------------------------*/
template <typename num_t> constexpr
num_t math::determinant(const mat4_t<num_t>& m) {
    return num_t{
        (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) -
        (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
        (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
        (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]) +

        (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) -
        (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
        (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) +
        (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +

        (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) -
        (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
        (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) +
        (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +

        (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
        (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
        (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
        (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) +

        (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) -
        (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
        (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) +
        (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +

        (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) -
        (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
        (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) +
        (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3])
    };
    //umm... wow
}

/*-------------------------------------
    4x4 Inverse
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::inverse(const mat4_t<num_t>& m) {
    // grab a pointer to the internal array in order to reduce the amount of dereferences
    // This helped to shrink the number of assembly instructions.
    const vec4_t<num_t>* const pm = m.m;

    //these operations appear only 2 times in the return value
    const num_t zwwx = pm[2][3] * pm[3][0];

    //these operations appear 3 times in the return value
    const num_t xxyy = pm[0][0] * pm[1][1];
    const num_t xxyz = pm[0][0] * pm[1][2];
    const num_t xzyy = pm[0][2] * pm[1][1];
    const num_t xyyz = pm[0][1] * pm[1][2];
    const num_t zwwy = pm[2][3] * pm[3][1];
    const num_t zwwz = pm[2][3] * pm[3][2];

    //these operations appear 4 times in the return value
    const num_t xxyw = pm[0][0] * pm[1][3];
    const num_t xyyx = pm[0][1] * pm[1][0];
    const num_t xyyw = pm[0][1] * pm[1][3];
    const num_t xzyx = pm[0][2] * pm[1][0];
    const num_t xzyw = pm[0][2] * pm[1][3];
    const num_t xwyx = pm[0][3] * pm[1][0];
    const num_t xwyy = pm[0][3] * pm[1][1];
    const num_t xwyz = pm[0][3] * pm[1][2];
    const num_t yyzw = pm[1][1] * pm[2][3];
    const num_t yzzw = pm[1][2] * pm[2][3];
    const num_t zxwy = pm[2][0] * pm[3][1];
    const num_t zxwz = pm[2][0] * pm[3][2];
    const num_t zxww = pm[2][0] * pm[3][3];
    const num_t zywx = pm[2][1] * pm[3][0];
    const num_t zywz = pm[2][1] * pm[3][2];
    const num_t zyww = pm[2][1] * pm[3][3];
    const num_t zzwx = pm[2][2] * pm[3][0];
    const num_t zzwy = pm[2][2] * pm[3][1];
    const num_t zzww = pm[2][2] * pm[3][3];

    return mat4_t<num_t>{
        (yzzw * pm[3][1]) - (pm[1][3] * zzwy) + (pm[1][3] * zywz) - (yyzw * pm[3][2]) - (pm[1][2] * zyww) + (pm[1][1] * zzww),
        (pm[0][3] * zzwy) - (pm[0][2] * zwwy) - (pm[0][3] * zywz) + (pm[0][1] * zwwz) + (pm[0][2] * zyww) - (pm[0][1] * zzww),
        (xzyw * pm[3][1]) - (xwyz * pm[3][1]) + (xwyy * pm[3][2]) - (xyyw * pm[3][2]) - (xzyy * pm[3][3]) + (xyyz * pm[3][3]),
        (xwyz * pm[2][1]) - (xzyw * pm[2][1]) - (xwyy * pm[2][2]) + (xyyw * pm[2][2]) + (pm[0][2] * yyzw) - (pm[0][1] * yzzw),
        (pm[1][3] * zzwx) - (yzzw * pm[3][0]) - (pm[1][3] * zxwz) + (pm[1][0] * zwwz) + (pm[1][2] * zxww) - (pm[1][0] * zzww),
        (pm[0][2] * zwwx) - (pm[0][3] * zzwx) + (pm[0][3] * zxwz) - (pm[0][0] * zwwz) - (pm[0][2] * zxww) + (pm[0][0] * zzww),
        (xwyz * pm[3][0]) - (xzyw * pm[3][0]) - (xwyx * pm[3][2]) + (xxyw * pm[3][2]) + (xzyx * pm[3][3]) - (xxyz * pm[3][3]),
        (xzyw * pm[2][0]) - (xwyz * pm[2][0]) + (xwyx * pm[2][2]) - (xxyw * pm[2][2]) - (xzyx * pm[2][3]) + (pm[0][0] * yzzw),
        (yyzw * pm[3][0]) - (pm[1][3] * zywx) + (pm[1][3] * zxwy) - (pm[1][0] * zwwy) - (pm[1][1] * zxww) + (pm[1][0] * zyww),
        (pm[0][3] * zywx) - (pm[0][1] * zwwx) - (pm[0][3] * zxwy) + (pm[0][0] * zwwy) + (pm[0][1] * zxww) - (pm[0][0] * zyww),
        (xyyw * pm[3][0]) - (xwyy * pm[3][0]) + (xwyx * pm[3][1]) - (xxyw * pm[3][1]) - (xyyx * pm[3][3]) + (xxyy * pm[3][3]),
        (xwyy * pm[2][0]) - (xyyw * pm[2][0]) - (xwyx * pm[2][1]) + (xxyw * pm[2][1]) + (xyyx * pm[2][3]) - (pm[0][0] * yyzw),
        (pm[1][2] * zywx) - (pm[1][1] * zzwx) - (pm[1][2] * zxwy) + (pm[1][0] * zzwy) + (pm[1][1] * zxwz) - (pm[1][0] * zywz),
        (pm[0][1] * zzwx) - (pm[0][2] * zywx) + (pm[0][2] * zxwy) - (pm[0][0] * zzwy) - (pm[0][1] * zxwz) + (pm[0][0] * zywz),
        (xzyy * pm[3][0]) - (xyyz * pm[3][0]) - (xzyx * pm[3][1]) + (xxyz * pm[3][1]) + (xyyx * pm[3][2]) - (xxyy * pm[3][2]),
        (xyyz * pm[2][0]) - (xzyy * pm[2][0]) + (xzyx * pm[2][1]) - (xxyz * pm[2][1]) - (xyyx * pm[2][2]) + (xxyy * pm[2][2])
    }
    *num_t{1} / determinant(m);
    // FML
}

/*-------------------------------------
    4x4 Transpose
-------------------------------------*/
template <typename num_t> constexpr
math::mat4_t<num_t> math::transpose(const mat4_t<num_t>& m) {
    return mat4_t<num_t>{
        m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
        m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
        m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
        m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]
    };
}

/*-------------------------------------
    4x4 Rotation
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::rotate(const mat4_t<num_t>& m, const vec3_t<num_t>& axis, num_t angle) {
    const num_t c           = LS_COS(angle);
    const num_t s           = LS_SIN(angle);
    const vec3_t<num_t>&& a = normalize<num_t>(axis);
    const num_t omc         = num_t{1} - c;
    const num_t xy          = (a.v[0] * a.v[1]) * omc;
    const num_t yz          = (a.v[1] * a.v[2]) * omc;
    const num_t zx          = (a.v[2] * a.v[0]) * omc;
    const num_t sx          = s * a.v[0];
    const num_t sy          = s * a.v[1];
    const num_t sz          = s * a.v[2];

    return m * mat4_t<num_t>{
        c + ((a.v[0] * a.v[0]) * omc),  xy + sz,                        zx - sy,                        num_t{0},
        xy - sz,                        c + ((a.v[1] * a.v[1]) * omc),  yz + sx,                        num_t{0},
        zx + sy,                        yz - sx,                        c + ((a.v[2] * a.v[2]) * omc),  num_t{0},
        num_t{0},                       num_t{0},                       num_t{0},                       num_t{1}
    };
}

/*-------------------------------------
    4x4 Scaling
-------------------------------------*/
template <typename num_t> constexpr
math::mat4_t<num_t> math::scale(const mat4_t<num_t>& m, const vec3_t<num_t>& scale) {
    return mat4_t<num_t>{
        m.m[0][0]*scale.v[0],   m.m[0][1],              m.m[0][2],              m.m[0][3],
        m.m[1][0],              m.m[1][1]*scale.v[1],   m.m[1][2],              m.m[1][3],
        m.m[2][0],              m.m[2][1],              m.m[2][2]*scale.v[2],   m.m[2][3],
        m.m[3][0],              m.m[3][1],              m.m[3][2],              m.m[3][3]
    };
}

/*-------------------------------------
    4x4 Translation
-------------------------------------*/
template <typename num_t> constexpr
math::mat4_t<num_t> math::translate(const mat4_t<num_t>& m, const vec3_t<num_t>& t) {
    return mat4_t<num_t>{
        m.m[0][0],          m.m[0][1],          m.m[0][2],          m.m[0][3],
        m.m[1][0],          m.m[1][1],          m.m[1][2],          m.m[1][3],
        m.m[2][0],          m.m[2][1],          m.m[2][2],          m.m[2][3],
        m.m[3][0]+t.v[0],   m.m[3][1]+t.v[1],   m.m[3][2]+t.v[2],   m.m[3][3]
    };
}

/*-------------------------------------
    4x4 Perspective
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::perspective(num_t fov, num_t aspect, num_t zNear, num_t zFar) {
    const num_t top     = LS_TAN(LS_DEG2RAD(fov) / num_t{2}) * zNear;
    const num_t bottom  = -top;
    const num_t xMin    = bottom * aspect;
    const num_t xMax    = top * aspect;
    const num_t zDelta  = zFar - zNear;

    return mat4_t<num_t>{
        (num_t{2}*zNear) / (xMax-xMin), num_t{0},                           num_t{0},                           num_t{0},
        num_t{0},                       (num_t{2}*zNear) / (top-bottom),    num_t{0},                           num_t{0},
        num_t{0},                       num_t{0},                           -(zFar+zNear) / zDelta,             num_t{-1},
        num_t{0},                       num_t{0},                           (num_t{-2}*zFar*zNear) / zDelta,    num_t{0}
    };
}

/*-------------------------------------
    4x4 Infinite Perspective
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::infinitePerspective(num_t fov, num_t aspect, num_t zNear) {
    const num_t top     = LS_TAN(LS_DEG2RAD(fov) / num_t{2}) * zNear;
    const num_t bottom  = -top;
    const num_t xMin    = bottom * aspect;
    const num_t xMax    = top * aspect;

    return mat4_t<num_t>{
        (num_t{2}*zNear) / (xMax-xMin), num_t{0},                           num_t{0},           num_t{0},
        num_t{0},                       (num_t{2}*zNear) / (top-bottom),    num_t{0},           num_t{0},
        num_t{0},                       num_t{0},                           num_t{-1},          num_t{-1},
        num_t{0},                       num_t{0},                           num_t{-2}*zNear,    num_t{0}
    };
}

/*-------------------------------------
    4x4 Ortho
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::ortho(num_t left, num_t right, num_t top, num_t bottom) {
    const num_t w = right - left;
    const num_t h = bottom - top;

    return mat4_t<num_t>{
        num_t{2} / w,       num_t{0},           num_t{0},   num_t{0},
        num_t{0},           num_t{2} / h,       num_t{0},   num_t{0},
        num_t{0},           num_t{0},           num_t{-1},  num_t{0},
        -(right+left) / w,  -(top+bottom) / h,  num_t{0},   num_t{1}
    };
}

/*-------------------------------------
    4x4 Ortho
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::ortho(num_t left, num_t right, num_t top, num_t bottom, num_t near, num_t far) {
    const num_t w = right - left;
    const num_t h = bottom - top;
    const num_t d = far - near;

    return mat4_t<num_t>{
        num_t{2} / w, num_t{0}, num_t{0}, num_t{0},
        num_t{0}, num_t{2} / h, num_t{0}, num_t{0},
        num_t{0}, num_t{0}, num_t{-2} / d, num_t{0},
        -(right + left) / w, -(top + bottom) / h, -(far + near) / d, num_t{1}
    };
}

/*-------------------------------------
    4x4 Frustum
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::frustum(num_t left, num_t right, num_t top, num_t bottom, num_t near, num_t far) {
    const num_t w = right - left;
    const num_t h = bottom - top;
    const num_t d = far - near;

    return mat4_t<num_t>{
        (num_t{2}*near) / w,    num_t{0},               num_t{0},                   num_t{0},
        num_t{0},               (num_t{2}*near) / h,    num_t{0},                   num_t{0},
        (right+left) / w,       (top+bottom) / h,       -(far+near) / d,            num_t{-1},
        num_t{0},               num_t{0},               (num_t{-2}*far*near) / d,   num_t{0}
    };
}

/*-------------------------------------
    4x4 LookAt
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::lookAt(const vec3_t<num_t>& pos, const vec3_t<num_t>& target, const vec3_t<num_t>& up) {
    const vec3_t<num_t> zAxis = normalize(pos - target);
    const vec3_t<num_t> xAxis = normalize(cross(up, zAxis));
    const vec3_t<num_t> yAxis = normalize(cross(zAxis, xAxis));

    return mat4_t<num_t>{
        xAxis.v[0],         yAxis.v[0],         zAxis.v[0],         num_t{0},
        xAxis.v[1],         yAxis.v[1],         zAxis.v[1],         num_t{0},
        xAxis.v[2],         yAxis.v[2],         zAxis.v[2],         num_t{0},
        -dot(xAxis, pos),   -dot(yAxis, pos),   -dot(zAxis, pos),   num_t{1}
    };
}

/*-------------------------------------
    4x4 Billboard
-------------------------------------*/
template <typename num_t> inline
math::mat4_t<num_t> math::billboard(const vec3_t<num_t>& pos, const mat4_t<num_t>& viewMat) {
    return mat4_t<num_t>{
        viewMat[0][0],  viewMat[1][0],  viewMat[2][0],  num_t{0},
        viewMat[0][1],  viewMat[1][1],  viewMat[2][1],  num_t{0},
        viewMat[0][2],  viewMat[1][2],  viewMat[2][2],  num_t{0},
        pos[0],         pos[1],         pos[2],         num_t{1}
    };
}

} // end ls namespace
