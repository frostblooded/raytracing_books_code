#include "aabb.h"

aabb::aabb() {}

aabb::aabb(const point3& a, const point3& b) 
	:_min(a), _max(b)
{}

point3 aabb::min() const {
	return _min;
}

point3 aabb::max() const {
	return _max;
}

bool aabb::hit(const ray& r, float tmin, float tmax) const {
	for (int a = 0; a < 3; a++) {
		auto invD = 1.0f / r.direction()[a];
		auto t0 = (min()[a] - r.origin()[a]) * invD;
		auto t1 = (max()[a] - r.origin()[a]) * invD;

		if (invD < 0.0f) {
			std::swap(t0, t1);
		}

		tmin = t0 > tmin ? t0 : tmin;
		tmax = t1 < tmax ? t1 : tmax;

		if (tmax <= tmin) {
			return false;
		}
	}

	return true;
}

