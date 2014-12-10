
#include "lightsky/math/math.h"
#include "lightsky/math/quat.h"

namespace ls {
namespace math {

/*
 * Quaternion Specializations
 */
LS_DEFINE_STRUCT_TYPE(quat_t, float);
LS_DEFINE_STRUCT_TYPE(quat_t, double);
LS_DEFINE_STRUCT_TYPE(quat_t, int);
LS_DEFINE_STRUCT_TYPE(quat_t, unsigned);
LS_DEFINE_STRUCT_TYPE(quat_t, medp_t);

} /* End math namespace */
} /* End ls namespace */

