/* 
 * File:   lsPerlinNoise.h
 * Author: miles
 *
 * Created on August 15, 2014, 9:23 PM
 */

#ifndef __LS_PERLIN_NOISE_H__
#define	__LS_PERLIN_NOISE_H__

#include "lsSetup.h"
#include "lsRandom.h"

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * Simple class to generate Perlin noise
 * 
 * Most of the code for this is based on a tutorial found here:
 * http://flafla2.github.io/2014/08/09/perlinnoise.html
 */
class lsPerlinNoise {
    private:
        /**
         * Pointer to a pseudo-random number generator that will be used to
         * generate random noise.
         */
        lsRandom* prng = nullptr;
        
        /**
         * An array of 512 randomly ordered integers that are used to generate
         * noise.
         */
        int* permutations = nullptr;
        
        /**
         * Helper function to blend different noise values.
         * 
         * @param doble
         * 
         * @return double
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
        lsPerlinNoise();
        
        /**
         * Seed Constructor
         * 
         * @param s
         * A long, unsigned integral value that will be used to seed the random
         * number generator.
         */
        lsPerlinNoise(unsigned long s);
        
        /**
         * Copy Constructor
         * 
         * @param A constant reference to another Perlin noise object
         */
        lsPerlinNoise(const lsPerlinNoise&);
        
        /**
         * Move Constructor
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param An R-Value reference to a Perlin noise object that's about to
         * go out of scope.
         */
        lsPerlinNoise(lsPerlinNoise&&);
        
        /**
         * Destructor
         * Frees all memory used by *this.
         */
        ~lsPerlinNoise();
        
        /**
         * Copy Operator
         * 
         * @param A constant reference to another Perlin noise object
         * 
         * @return A reference to *this.
         */
        lsPerlinNoise& operator=(const lsPerlinNoise&);
        
        /**
         * Move Operator
         * 
         * @param An R-Value reference to a Perlin noise object that's about to
         * go out of scope.
         * 
         * @return A reference to *this.
         */
        lsPerlinNoise& operator=(lsPerlinNoise&&);
        
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
        double getNoise(const math::vec3& point);
        
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
        double getOctaveNoise(const math::vec3& point, unsigned octaves, double persistance);
};

#endif	/* __LS_PERLIN_NOISE_H__ */

