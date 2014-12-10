
#include "lightsky/math/math.h"
#include "lightsky/math/mat4.h"

namespace ls {
namespace math {

/*
 * 4x4 Matrix Specializations
 */
LS_DEFINE_STRUCT_TYPE(mat4_t, float);
LS_DEFINE_STRUCT_TYPE(mat4_t, double);
LS_DEFINE_STRUCT_TYPE(mat4_t, int);
LS_DEFINE_STRUCT_TYPE(mat4_t, unsigned);
LS_DEFINE_STRUCT_TYPE(mat4_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
