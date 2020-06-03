#pragma once

#include "material.h"
#include "hitable.h"

struct xz_rect : public hitable
{
	xz_rect();
	xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, shared_ptr<material> mat);

	virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const;

	shared_ptr<material> mp;
	float x0, x1, z0, z1, k;
};



