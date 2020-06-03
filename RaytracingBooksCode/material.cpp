#include "material.h"

color material::emitted(double u, double v, const point3& p) const {
	return color(0, 0, 0);
}
