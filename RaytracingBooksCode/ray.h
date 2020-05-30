#ifndef RAYH
#define RAYH

#include "vec3.h"

struct ray
{
    ray() : orig(0, 0, 0), dir(0, 0, 0) {}

    ray(const vec3& origin, const vec3& direction, float time = 0.0)
        : orig(origin), dir(direction), tm(time)
    {}

    inline vec3 origin() const { return orig; }
    inline vec3 direction() const { return dir; }
    inline float time() const { return tm; }
    inline vec3 at(const float t) const { return orig + dir * t; }

    vec3 orig;
    vec3 dir;
    double tm;
};

#endif
