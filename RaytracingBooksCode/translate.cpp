#include "translate.h"

translate::translate(shared_ptr<hitable> p, const vec3& displacement)
	: ptr(p), offset(displacement)
{}

bool translate::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	ray moved_r(r.origin() - offset, r.direction(), r.time());

	if (!ptr->hit(moved_r, t_min, t_max, rec)) {
		return false;
	}

	rec.p += offset;
	rec.set_face_normal(moved_r, rec.normal);

	return true;
}

bool translate::bounding_box(float t0, float t1, aabb& output_box) const {
	if (!ptr->bounding_box(t0, t1, output_box)) {
		return false;
	}

	output_box = aabb(output_box.min() + offset, output_box.max() + offset);
	return true;
}

