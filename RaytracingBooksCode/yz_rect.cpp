#include "yz_rect.h"

yz_rect::yz_rect() {}

yz_rect::yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, shared_ptr<material> mat)
	: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat)
{}

bool yz_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
	auto t = (k - r.origin().x()) / r.direction().x();

	if (t < t0 || t > t1) {
		return false;
	}

	auto y = r.origin().y() + t * r.direction().y();
	auto z = r.origin().z() + t * r.direction().z();

	if (y < y0 || y > y1 || z < z0 || z > z1) {
		return false;
	}

	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	auto outward_normal = vec3(1, 0, 0);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mp;
	rec.p = r.at(t);
	return true;
}

bool yz_rect::bounding_box(float t0, float t1, aabb& output_box) const {
	output_box = aabb(point3(k - 0.0001, y0, z0), point3(k + 0.0001, y1, z1));
	return true;
}
