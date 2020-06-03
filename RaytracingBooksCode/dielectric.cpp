#include "dielectric.h"
#include "random.h"

dielectric::dielectric(float ri)
	: ref_idx(ri)
{}

bool dielectric::refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) const
{
	vec3 uv = v.unit_vector();
	float dt = uv.dot(n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
	
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}

	return false;
}

float dielectric::schlick(float cosine, float ref_idx) const {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool dielectric::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
{
	vec3 outward_normal;
	vec3 reflected = r_in.direction().reflect(rec.normal);
	float ni_over_nt;
	attenuation = vec3(1, 1, 1);
	vec3 refracted;
	float reflect_prob;
	float cosine;

	if (rec.front_face) {
		ni_over_nt = ref_idx;
		cosine = ref_idx * r_in.direction().dot(rec.normal) / r_in.direction().length();
	}
	else {
		ni_over_nt = 1 / ref_idx;
		cosine = -r_in.direction().dot(rec.normal) / r_in.direction().length();
	}

	if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
		reflect_prob = schlick(cosine, ref_idx);
	}
	else {
		reflect_prob = 1.0;
	}

	if (random() < reflect_prob) {
		scattered = ray(rec.p, reflected, r_in.time());
	}
	else {
		scattered = ray(rec.p, refracted, r_in.time());
	}

	return true;
}

