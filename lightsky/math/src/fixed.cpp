
#include "lightsky/math/types.h"
#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

/*-------------------------------------
    Fixed-Point Template Specializations
-------------------------------------*/
LS_DEFINE_CLASS_TYPE(fixed_t,    int32_t,    7); // 24.7 (-1 for the sign)
LS_DEFINE_CLASS_TYPE(fixed_t,    int32_t,    15); // 16.15
LS_DEFINE_CLASS_TYPE(fixed_t,    int32_t,    23); // 8.23

LS_DEFINE_CLASS_TYPE(fixed_t,    int64_t,    15); // 48.15
LS_DEFINE_CLASS_TYPE(fixed_t,    int64_t,    31); // 32.31
LS_DEFINE_CLASS_TYPE(fixed_t,    int64_t,    47); // 16.47

LS_DEFINE_CLASS_TYPE(fixed_t,    uint32_t,   8); // 24.8 (-1 for the sign)
LS_DEFINE_CLASS_TYPE(fixed_t,    uint32_t,   16); // 16.16
LS_DEFINE_CLASS_TYPE(fixed_t,    uint32_t,   24); // 8.24

LS_DEFINE_CLASS_TYPE(fixed_t,    uint64_t,   16); // 48.16
LS_DEFINE_CLASS_TYPE(fixed_t,    uint64_t,   32); // 32.32
LS_DEFINE_CLASS_TYPE(fixed_t,    uint64_t,   48); // 16.48

} /* End math namespace */
} /* End ls namespace */
