#ifndef MATERIALH
#define MATERIALH

#include "hit_record.h"
#include "ray.h"

struct material
{
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

#endif
