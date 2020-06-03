#include "xy_rect.h"

xy_rect::xy_rect() {}

xy_rect::xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, shared_ptr<material> mat)
	: x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat)
{}

bool xy_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
	auto t = (k - r.origin().z()) / r.direction().z();

	if (t < t0 || t > t1) {
		return false;
	}

	auto x = r.origin().x() + t * r.direction().x();
	auto y = r.origin().y() + t * r.direction().y();

	if (x < x0 || x > x1 || y < y0 || y > y1) {
		return false;
	}

	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);
	rec.t = t;
	auto outward_normal = vec3(0, 0, 1);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mp;
	rec.p = r.at(t);
	return true;
}

bool xy_rect::bounding_box(float t0, float t1, aabb& output_box) const {
	output_box = aabb(point3(x0, y0, k - 0.0001), point3(x1, y1, k + 0.0001));
	return true;
}
