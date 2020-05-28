#ifndef LAMBERTIANH
#define LAMBERTIANH

#include "material.h"
#include "../../src/random_in_unit_sphere.h"

struct lambertian : public material
{
    lambertian(const vec3 &a) : albedo(a) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    vec3 albedo;
};

#endif
