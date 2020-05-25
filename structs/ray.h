#ifndef RAYH
#define RAYH

struct ray
{
    ray() {}
    ray(const vec3 &a, const vec3 &b) : A(a), B(b) {}
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(const float t) { return A + B * t; }

    vec3 A;
    vec3 B;
};

#endif
