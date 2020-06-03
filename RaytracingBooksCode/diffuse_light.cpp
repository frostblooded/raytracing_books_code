#include "diffuse_light.h"

diffuse_light::diffuse_light(shared_ptr<texture> a)
	: emit(a)
{}

bool diffuse_light::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
	return false;
}

color diffuse_light::emitted(double u, double v, const point3& p) const {
	return emit->value(u, v, p);
}

