#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "ray.h"
#include "hit_record.h"

struct sphere : public hitable
{
    sphere() {}
    sphere(const vec3 &cen, const float r) : center(cen), radius(r) {}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    vec3 center;
    float radius;
};

#endif
