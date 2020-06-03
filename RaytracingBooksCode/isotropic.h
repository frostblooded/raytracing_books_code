#pragma once

#include "material.h"
#include "texture.h"
#include "ray.h"

struct isotropic : public material
{
	isotropic(shared_ptr<texture> a);
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;

	shared_ptr<texture> albedo;
};

