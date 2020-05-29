#ifndef METALH
#define METALH

#include "material.h"
#include "random.h"

struct metal : public material
{
    metal(const vec3& a, float f) : albedo(a)
    {
        if (f >= 1)
        {
            f = 1;
        }

        fuzz = f;
    }

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        vec3 reflected = r_in.direction().unit_vector().reflect(rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return scattered.direction().dot(rec.normal) > 0;
    }

    vec3 albedo;
    float fuzz;
};

#endif
