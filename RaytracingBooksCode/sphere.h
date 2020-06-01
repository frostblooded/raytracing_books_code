#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "ray.h"
#include "hit_record.h"
#include "material.h"

struct sphere : public hitable
{
    sphere() : center(0, 0, 0), radius(0), mat(nullptr) {}
    sphere(const vec3& cen, const float r, shared_ptr<material> m) : center(cen), radius(r), mat(m) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    bool bounding_box(float t0, float t1, aabb& output_box) const;

    static void get_uv(const vec3& p, float& u, float& v);

    vec3 center;
    float radius;
    shared_ptr<material> mat;
};

#endif
