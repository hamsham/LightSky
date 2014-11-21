
#include "lightsky/math/math.h"
#include "lightsky/math/perlinNoise.h"

namespace ls {
namespace math {

/*-------------------------------------
    Perlin Noise Specializations
-------------------------------------*/
LS_DEFINE_CLASS_TYPE(perlinNoise_t, float);
LS_DEFINE_CLASS_TYPE(perlinNoise_t, double);
LS_DEFINE_CLASS_TYPE(perlinNoise_t, int);
LS_DEFINE_CLASS_TYPE(perlinNoise_t, unsigned);
LS_DEFINE_CLASS_TYPE(perlinNoise_t, medp_t);

} /* End math namespace */
} /* End ls namespace */
