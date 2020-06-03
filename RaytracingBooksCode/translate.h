#pragma once

#include "hitable.h"

struct translate : public hitable
{
	translate(shared_ptr<hitable> p, const vec3& displacement);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const;

    shared_ptr<hitable> ptr;
    vec3 offset;
};

