#pragma once

#include "hitable.h"

struct rotate_y : public hitable
{
	rotate_y(shared_ptr<hitable> p, float angle);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const;

    shared_ptr<hitable> ptr;
    float sin_theta;
    float cos_theta;
    bool hasbox;
    aabb bbox;
};

