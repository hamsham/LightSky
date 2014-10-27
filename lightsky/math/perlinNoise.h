/* 
 * File:   math/perlinNoise.h
 * Author: miles
 *
 * Created on August 15, 2014, 9:23 PM
 */

#ifndef __LS__MATH_PERLIN_NOISE_H__
#define	__LS__MATH_PERLIN_NOISE_H__

#include <chrono>
#include <algorithm>

#include "lightsky/math/vec3.h"
#include "lightsky/utils/randomNum.h"

namespace ls {
namespace math {

/**
 * @brief Simple class to generate Perlin noise
 * 
 * Most of the code for this is based on a tutorial found here:
 * http://flafla2.github.io/2014/08/09/perlinnoise.html
 */
template <typename num_t = float>
class perlinNoise_t {
    private:
        /**
         * Pointer to a pseudo-random number generator that will be used to
         * generate random noise.
         */
        utils::randomNum* prng = nullptr;
        
        /**
         * An array of 512 randomly ordered integers that are used to generate
         * noise.
         */
        int* permutations = nullptr;
        
        /**
         * Helper function to blend different noise values.
         * 
         * @param num_t
         * 
         * @return num_t
         */
        static double fade(double);
        
        /**
         * Linearly interpolate two values over a certain percentage.
         * 
         * @param a
         * The value to be interpolated to B.
         * 
         * @param b
         * A reference value that A will interpolate towards.
         * 
         * @param x
         * The percent to interpolate A->B
         * 
         * @return A linear interpolation of A->B
         */
        static double lerp(double a, double b, double x);
        
        /**
         * Generate a gradient value based on a hash function at the points x,
         * y, and z.
         * 
         * @param hash
         * 
         * @param x
         * 
         * @param y
         * 
         * @param z
         * 
         * @return A gradient value that will assist in smoothly transitioning
         * from one set of points to another.
         */
        static double grad(int hash, double x, double y, double z);
        
    public:
        /**
         * Constructor
         */
        perlinNoise_t();
        
        /**
         * Seed Constructor
         * 
         * @param s
         * A long, unsigned integral value that will be used to seed the random
         * number generator.
         */
        explicit perlinNoise_t(unsigned long s);
        
        /**
         * Copy Constructor
         * 
         * @param A constant reference to another Perlin noise object
         */
        perlinNoise_t(const perlinNoise_t&);
        
        /**
         * Move Constructor
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param An R-Value reference to a Perlin noise object that's about to
         * go out of scope.
         */
        perlinNoise_t(perlinNoise_t&&);
        
        /**
         * Destructor
         * Frees all memory used by *this.
         */
        ~perlinNoise_t();
        
        /**
         * Copy Operator
         * 
         * @param A constant reference to another Perlin noise object
         * 
         * @return A reference to *this.
         */
        perlinNoise_t& operator=(const perlinNoise_t&);
        
        /**
         * Move Operator
         * 
         * @param An R-Value reference to a Perlin noise object that's about to
         * go out of scope.
         * 
         * @return A reference to *this.
         */
        perlinNoise_t& operator=(perlinNoise_t&&);
        
        /**
         * Seed the random number generator in order to generate new noise.
         */
        void seed();
        
        /**
         * Seed the random number generator in order to generate new noise.
         * 
         * @param s
         * A long, unsigned integral value that will be used to seed the random
         * number generator.
         */
        void seed(unsigned long s);
        
        /**
         * Get a [pseudo] randomly generated noise value within a 3D Cartesian
         * coordinate space.
         * 
         * @param point
         * A point within a linear 3D space from which a noise value will be
         * calculated.
         * 
         * @return A Perlin noise value, calculated at the point specified by
         * the input parameter. This value will be between [-1,1].
         */
        template <typename point_t>
        num_t getNoise(const vec3_t<point_t>& point);
        
        /**
         * Get a [pseudo] randomly generated noise value within a 3D Cartesian
         * coordinate space. This value will be modified by a frequency
         * specified by the number of octaves and persistence provided.
         * 
         * @see http://freespace.virgin.net/hugo.elias/models/m_perlin.htm for
         * more details.
         * 
         * @param point
         * A point within a linear 3D space from which a noise value will be
         * calculated.
         * 
         * @param octaves
         * The inverse of the number of times that the noise function will be
         * added onto itself (for example, 1/2, 1/4, 1/sqrt(2), etc.).
         * 
         * @param persistance
         * The length of effect that the noise value at a given point will have
         * on other noise values.
         * 
         * @return A Perlin noise value, calculated at the point specified by
         * the input parameter. This value will be between [-1,1].
         */
        num_t getOctaveNoise(const vec3_t<num_t>& point, unsigned octaves, num_t persistance);
};

/*-------------------------------------
    Perlin Noise Specializations
-------------------------------------*/
LS_DECLARE_CLASS_TYPE(perlinNoisef,     perlinNoise_t, float);
LS_DECLARE_CLASS_TYPE(perlinNoised,     perlinNoise_t, double);
LS_DECLARE_CLASS_TYPE(perlinNoisei,     perlinNoise_t, int);
LS_DECLARE_CLASS_TYPE(perlinNoiseuu,    perlinNoise_t, unsigned);
LS_DECLARE_CLASS_TYPE(perlinNoisex,     perlinNoise_t, medp_t);

} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/perlinNoise_impl.h"

#endif	/* __LS__MATH_PERLIN_NOISE_H__ */
