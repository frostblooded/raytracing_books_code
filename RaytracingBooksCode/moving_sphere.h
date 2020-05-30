#pragma once

#include "hitable.h"
#include "vec3.h"

struct moving_sphere : public hitable
{
	moving_sphere();
	moving_sphere(point3 cen0, point3 cen1, float t0, float t1, float r, shared_ptr<material> m);

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
	point3 center(float time) const;

	point3 center0, center1;
	float time0, time1;
	float radius;
	shared_ptr<material> mat_ptr;
};

