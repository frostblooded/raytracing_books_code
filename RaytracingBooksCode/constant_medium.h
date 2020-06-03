#pragma once

#include "hitable.h"
#include "texture.h"

struct constant_medium : public hitable
{
    constant_medium(shared_ptr<hitable> b, float d, shared_ptr<texture> a);
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const;

    shared_ptr<hitable> boundary;
    shared_ptr<material> phase_function;
    float neg_inv_density;
};

