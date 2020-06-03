#include "constant_medium.h"
#include "isotropic.h"
#include <iostream>

using namespace std;

constant_medium::constant_medium(shared_ptr<hitable> b, float d, shared_ptr<texture> a)
	: boundary(b), neg_inv_density(-1 / d)
{
	phase_function = make_shared<isotropic>(a);
}

bool constant_medium::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	const bool enableDebug = false;
	const bool debugging = enableDebug && random() < 0.00001;

	hit_record rec1, rec2;

	if (!boundary->hit(r, -INFINITY, INFINITY, rec1)) {
		return false;
	}

	if (!boundary->hit(r, rec1.t + 0.0001, INFINITY, rec2)) {
		return false;
	}

	if (debugging) {
		cerr << "\nt0 = " << rec1.t << ", t1 = " << rec2.t << "\n";
	}

	if (rec1.t < t_min) { rec1.t = t_min; }
	if (rec2.t > t_max) { rec2.t = t_max; }

	if (rec1.t >= rec2.t) {
		return false;
	}

	if (rec1.t < 0) {
		rec1.t = 0;
	}

	const auto ray_length = r.direction().length();
	const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
	const auto hit_distance = neg_inv_density * log(random());

	if (hit_distance > distance_inside_boundary) {
		return false;
	}

	rec.t = rec1.t + hit_distance / ray_length;
	rec.p = r.at(rec.t);

	if (debugging) {
		std::cerr << "hit_distance = " << hit_distance << '\n'
			<< "rec.t = " << rec.t << '\n'
			<< "rec.p = " << rec.p << '\n';
	}

	rec.normal = vec3(1, 0, 0);
	rec.front_face = true;
	rec.mat_ptr = phase_function;

	return true;
}

bool constant_medium::bounding_box(float t0, float t1, aabb& output_box) const {
	return boundary->bounding_box(t0, t1, output_box);
}
