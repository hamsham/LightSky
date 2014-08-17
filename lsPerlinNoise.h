/* 
 * File:   lsPerlinNoise.h
 * Author: miles
 *
 * Created on August 15, 2014, 9:23 PM
 */

#ifndef __LS_PERLIN_NOISE_H__
#define	__LS_PERLIN_NOISE_H__

#include <cstdint>
#include <chrono>
#include <algorithm>

#include "lsSetup.h"
#include "include/lsRandom.h"

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
    enum : unsigned {
        MAX_PERMUTATIONS = 512
    };
    
    private:
        lsRandom* prng = nullptr;
        int* permutations = nullptr;
        
        static double fade(double);
        static double lerp(double a, double b, double x);
        static double grad(int hash, double x, double y, double z);
        
    public:
        lsPerlinNoise();
        lsPerlinNoise(unsigned long s);
        lsPerlinNoise(const lsPerlinNoise&);
        lsPerlinNoise(lsPerlinNoise&&);
        
        ~lsPerlinNoise();
        
        lsPerlinNoise& operator=(const lsPerlinNoise&);
        lsPerlinNoise& operator=(lsPerlinNoise&&);
        
        void seed();
        void seed(unsigned long s);
        
        double getNoise(const math::vec3&);
        double getOctaveNoise(const math::vec3&, unsigned octaves, double persistance);
};

#endif	/* __LS_PERLIN_NOISE_H__ */

