
#include "lightsky/math/math.h"
#include "lightsky/math/mat3.h"

namespace ls {
namespace math {

/*
 * 3x3 Matrix Specializations
 */
LS_DEFINE_CLASS_TYPE(mat3_t, float);
LS_DEFINE_CLASS_TYPE(mat3_t, double);
LS_DEFINE_CLASS_TYPE(mat3_t, int);
LS_DEFINE_CLASS_TYPE(mat3_t, unsigned);
LS_DEFINE_CLASS_TYPE(mat3_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
