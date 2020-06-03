#include "xz_rect.h"

xz_rect::xz_rect() {}

xz_rect::xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, shared_ptr<material> mat)
	: x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat)
{}

bool xz_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
	auto t = (k - r.origin().y()) / r.direction().y();

	if (t < t0 || t > t1) {
		return false;
	}

	auto x = r.origin().x() + t * r.direction().x();
	auto z = r.origin().z() + t * r.direction().z();

	if (x < x0 || x > x1 || z < z0 || z > z1) {
		return false;
	}

	rec.u = (x - x0) / (x1 - x0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	auto outward_normal = vec3(0, 1, 0);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mp;
	rec.p = r.at(t);
	return true;
}

bool xz_rect::bounding_box(float t0, float t1, aabb& output_box) const {
	output_box = aabb(point3(x0, k - 0.0001, z0), point3(x1, k + 0.0001, z1));
	return true;
}
