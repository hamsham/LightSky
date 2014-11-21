
namespace ls {
namespace math {

/*-----------------------------------------------------------------------------
    Enumerations
-----------------------------------------------------------------------------*/
enum : unsigned {
    MAX_PERMUTATIONS = 512
};
    

/*-----------------------------------------------------------------------------
    Perlin Noise Class Definitions
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Constructor
-------------------------------------*/
template <typename num_t>
perlinNoise_t<num_t>::perlinNoise_t() :
    perlinNoise_t{(long unsigned)std::chrono::system_clock::now().time_since_epoch().count()}
{}

/*-------------------------------------
    Random Seed Constructor
-------------------------------------*/
template <typename num_t>
perlinNoise_t<num_t>::perlinNoise_t(unsigned long s) :
    prng{new utils::randomNum{}},
    permutations{new int[MAX_PERMUTATIONS]}
{
    this->seed(s);
}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
template <typename num_t>
perlinNoise_t<num_t>::perlinNoise_t(const perlinNoise_t& pn) :
    prng{new utils::randomNum{*(pn.prng)}},
    permutations{new int[MAX_PERMUTATIONS]}
{
    std::copy(pn.permutations, pn.permutations+MAX_PERMUTATIONS, permutations);
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
template <typename num_t>
perlinNoise_t<num_t>::perlinNoise_t(perlinNoise_t&& pn) :
    prng{pn.prng},
    permutations{pn.permutations}
{
    pn.prng = nullptr;
    pn.permutations = nullptr;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
template <typename num_t>
perlinNoise_t<num_t>::~perlinNoise_t() {
    delete prng;
    delete [] permutations;
}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
template <typename num_t>
perlinNoise_t<num_t>& perlinNoise_t<num_t>::operator=(const perlinNoise_t& pn) {
    *prng = *pn.prng;
    
    std::copy(pn.permutations, pn.permutations+MAX_PERMUTATIONS, permutations);
    
    return *this;
}


/*-------------------------------------
    Move Constructor
-------------------------------------*/
template <typename num_t>
perlinNoise_t<num_t>& perlinNoise_t<num_t>::operator=(perlinNoise_t&& pn) {
    delete prng;
    prng = pn.prng;
    pn.prng = nullptr;
    
    delete [] permutations;
    permutations = pn.permutations;
    pn.permutations = nullptr;
    
    return *this;
}

/*-------------------------------------
    Regenerate the noise permutations
-------------------------------------*/
template <typename num_t>
void perlinNoise_t<num_t>::seed(unsigned long s) {
    prng->seed(s);
    
    // initialize all of the numbers between 0-255
    for (int i = 0; i < 256; ++i) {
        permutations[i] = i;
    }
    
    // shuffle all of the numbers in the permutations list
    for (unsigned i = 0; i < 256; ++i) {
        unsigned index = (*prng)() % 256;
        int a = permutations[i];
        permutations[i] = permutations[index];
        permutations[index] = a;
    }
    
    // repeat all of the numbers
    for (unsigned i = 256, j = 0; i < MAX_PERMUTATIONS; ++i, ++j) {
        permutations[i] = permutations[j];
    }
}

/*-------------------------------------
    Regenerate the noise permutations
-------------------------------------*/
template <typename num_t>
void perlinNoise_t<num_t>::seed() {
    this->seed((long unsigned)std::chrono::system_clock::now().time_since_epoch().count());
}

/*-------------------------------------
    Blend real/float values so they are closer to integral values.
    This was defined by Ken Perlin.
-------------------------------------*/
template <typename num_t>
double perlinNoise_t<num_t>::fade(double t) {
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

/*-------------------------------------
    Linearly interpolate between gradient values
-------------------------------------*/
template <typename num_t>
double perlinNoise_t<num_t>::lerp(double a, double b, double x) {
    return a + x * (b - a);
}

/*-------------------------------------
    Calculate the dot product of a randomly selected gradient vector
    This was defined by Ken Perlin.
-------------------------------------*/
template <typename num_t>
double perlinNoise_t<num_t>::grad(int hash, double x, double y, double z) {
    switch(hash & 0xF) {
        case 0x0:   return  x + y;
        case 0x1:   return -x + y;
        case 0x2:   return  x - y;
        case 0x3:   return -x - y;
        case 0x4:   return  x + z;
        case 0x5:   return -x + z;
        case 0x6:   return  x - z;
        case 0x7:   return -x - z;
        case 0x8:   return  y + z;
        case 0x9:   return -y + z;
        case 0xA:   return  y - z;
        case 0xB:   return -y - z;
        case 0xC:   return  y + x;
        case 0xD:   return -y + z;
        case 0xE:   return  y - x;
        case 0xF:   return -y - z;
    }
    return 0.0;
}

/*-------------------------------------
    Generate the noise function
    
    This implementation was as a combination of serveral sources:
    http://flafla2.github.io/2014/08/09/perlinnoise.html
    https://github.com/sol-prog/Perlin_Noise/blob/master/PerlinNoise.cpp
    http://staffwww.itn.liu.se/~stegu/
    http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
-------------------------------------*/
template <typename num_t>
template <typename point_t>
num_t perlinNoise_t<num_t>::getNoise(const vec3_t<point_t>& point) {
    // create coordinates for a "unit cube"
    int xi = (int)std::floor(point[0]) & 255;
    int yi = (int)std::floor(point[1]) & 255;
    int zi = (int)std::floor(point[2]) & 255;
    
    double xr = point[0] - std::floor(point[0]);
    double yr = point[1] - std::floor(point[1]);
    double zr = point[2] - std::floor(point[2]);
    
    // compute how each value fades across u/v/w
    double u = fade(xr);
    double v = fade(yr);
    double w = fade(zr);
    
    int a0 = permutations[xi    ] + yi;
    int a1 = permutations[a0    ] + zi;
    int a2 = permutations[a0 + 1] + zi;
    int b0 = permutations[xi + 1] + yi;
    int b1 = permutations[b0    ] + zi;
    int b2 = permutations[b0 + 1] + zi;
    
    double x10 = lerp(grad(permutations[a1],    xr, yr,     zr),    grad(permutations[b1],      xr-1,   yr,     zr),    u);
    double x11 = lerp(grad(permutations[a2],    xr, yr-1,   zr),    grad(permutations[b2],      xr-1,   yr-1,   zr),    u);
    double x12 = lerp(grad(permutations[a1+1],  xr, yr,     zr-1),  grad(permutations[b1+1],    xr-1,   yr,     zr-1),  u);
    double x13 = lerp(grad(permutations[a2+1],  xr, yr-1,   zr-1),  grad(permutations[b2+1],    xr-1,   yr-1,   zr-1),  u);
    
    double y10 = lerp(x10, x11, v);
    double y11 = lerp(x12, x13, v);
    
    return (num_t)lerp(y10, y11, w);
}

/*-------------------------------------
    Generate the noise function with an octave (perturbations).
    
    This portion was found here:
    http://flafla2.github.io/2014/08/09/perlinnoise.html
-------------------------------------*/
template <typename num_t>
num_t perlinNoise_t<num_t>::getOctaveNoise(const vec3_t<num_t>& point, unsigned octaves, num_t persistence) {
    num_t total = num_t{0};
    num_t frequency = num_t{1};
    num_t amplitude = num_t{1};
    num_t maxValue = num_t{1};
    
    for (unsigned i = 0; i < octaves; ++i) {
        total += getNoise(point * frequency * amplitude);
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= num_t{2};
    }
    
    return total/maxValue;
}

} // end math namespace
} // end ls namespace
