
#include "lightsky/math/math.h"
#include "lightsky/math/vec2.h"

namespace ls {
namespace math {

/*
 * 2D Vector Specializations
 */
LS_DEFINE_STRUCT_TYPE(vec2_t, float);
LS_DEFINE_STRUCT_TYPE(vec2_t, double);
LS_DEFINE_STRUCT_TYPE(vec2_t, int);
LS_DEFINE_STRUCT_TYPE(vec2_t, unsigned);
LS_DEFINE_STRUCT_TYPE(vec2_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
