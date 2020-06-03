#pragma once

#include "material.h"
#include "hitable.h"

struct xy_rect : public hitable
{
	xy_rect();
	xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, shared_ptr<material> mat);

	virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const;

	shared_ptr<material> mp;
	float x0, x1, y0, y1, k;
};

