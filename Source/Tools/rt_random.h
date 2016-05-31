#pragma once

#include "rt_types.h"
#include "math.h"
#include <stdint.h>
#ifndef WIN32
#define UINT32_MAX		(4294967295U)
#endif


namespace vis
{
    void rand_seed(uint32_t seed);

    int32_t rand_i(); // 0 - 32767
    int32_t rand_i(uint32_t& seed);
    int32_t rand_i(int32_t rmin, int32_t rmax);
    int32_t rand_i(int32_t rmin, int32_t rmax, uint32_t& seed);

    float rand_f();
    float rand_f(uint32_t& seed);
    float rand_f(float rmin, float rmax);
    float rand_f(float rmin, float rmax, uint32_t& seed);


    ////////////////////////////////////////////////////////////////

    extern uint32_t s_random_seed;

    inline void rand_seed(uint32_t seed)
    {
        s_random_seed = seed;
    }

    inline int32_t rand_i()
    {
        return rand_i(s_random_seed);
    }

    inline int32_t rand_i(uint32_t& seed)
    {
        return ((seed = seed * 214013L + 2531011L) >> 16) & 32767;
    }

    inline int32_t rand_i(int32_t rmin, int32_t rmax)
    {
        return rand_i(rmin, rmax, s_random_seed);
    }

    inline int32_t rand_i(int32_t rmin, int32_t rmax, uint32_t& seed)
    {
        return rmin + rand_i() % (rmax - rmin);
    }

    inline float rand_f()
    {
        return rand_f(s_random_seed);
    }

    inline float rand_f(uint32_t& seed)
    {
        return (float)rand_i(seed) * (1.0f / 32767.0f);
    }

    inline float rand_f(float rmin, float rmax)
    {
        return rand_f(rmin, rmax, s_random_seed);
    }

    inline float rand_f(float rmin, float rmax, uint32_t& seed)
    {
        return rmin + rand_f(seed) * (rmax - rmin);
    }
}
