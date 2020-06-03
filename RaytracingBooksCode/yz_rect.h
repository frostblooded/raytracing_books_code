#pragma once

#include "material.h"
#include "hitable.h"

struct yz_rect : public hitable
{
	yz_rect();
	yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, shared_ptr<material> mat);

	virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const;

	shared_ptr<material> mp;
	float y0, y1, z0, z1, k;
};


