#ifndef RAYH
#define RAYH

#include "vec3.h"

struct ray
{
    ray() : A(0, 0, 0), B(0, 0, 0) {}
    ray(const vec3& a, const vec3& b) : A(a), B(b) {}
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 at(const float t) const { return A + B * t; }

    vec3 A;
    vec3 B;
};

#endif
