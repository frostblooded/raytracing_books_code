#ifndef LAMBERTIANH
#define LAMBERTIANH

#include "material.h"
#include "random.h"
#include "texture.h"

struct lambertian : public material
{
    lambertian(shared_ptr<texture> a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p, r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

    shared_ptr<texture> albedo;
};

#endif
