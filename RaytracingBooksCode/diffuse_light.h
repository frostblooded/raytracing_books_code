#pragma once

#include "material.h"
#include "texture.h"

struct diffuse_light : public material
{
	diffuse_light(shared_ptr<texture> a);
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
	virtual color emitted(double u, double v, const point3& p) const;

	shared_ptr<texture> emit;
};

