
#include "lightsky/math/math.h"
#include "lightsky/math/vec3.h"

namespace ls {
namespace math {

/*
 * 3D Vector Specializations
 */
LS_DEFINE_STRUCT_TYPE(vec3_t, float);
LS_DEFINE_STRUCT_TYPE(vec3_t, double);
LS_DEFINE_STRUCT_TYPE(vec3_t, int);
LS_DEFINE_STRUCT_TYPE(vec3_t, unsigned);
LS_DEFINE_STRUCT_TYPE(vec3_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
