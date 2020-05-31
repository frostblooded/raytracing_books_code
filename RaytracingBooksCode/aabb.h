#pragma once

#include "ray.h"

struct aabb
{
	aabb();
	aabb(const point3& a, const point3& b);

	point3 min() const;
	point3 max() const;
	bool hit(const ray& r, float tmin, float tmax) const;

	point3 _min;
	point3 _max;
};

