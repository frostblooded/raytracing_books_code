#pragma once

#include "vec3.h"
#include "material.h"

struct dielectric : public material
{
	dielectric(float ri);

	bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) const;
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
	float schlick(float cosine, float ref_idx) const;

	float ref_idx;
};

