#pragma once

#include "hitable_list.h"

struct box : public hitable
{
	box();
	box(const point3& p0, const point3& p1, shared_ptr<material> ptr);

	virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const;

	point3 box_min;
	point3 box_max;
	hitable_list sides;
};

