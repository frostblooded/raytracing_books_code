#include "flip_face.h"

flip_face::flip_face(shared_ptr<hitable> p)
	: ptr(p)
{}

bool flip_face::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	if (!ptr->hit(r, t_min, t_max, rec)) {
		return false;
	}

	rec.front_face = !rec.front_face;
	return true;
}
bool flip_face::bounding_box(float t0, float t1, aabb& output_box) const {
	return ptr->bounding_box(t0, t1, output_box);
}

