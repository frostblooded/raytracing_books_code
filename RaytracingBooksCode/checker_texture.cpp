#include "checker_texture.h"

checker_texture::checker_texture() {}

checker_texture::checker_texture(shared_ptr<texture> t0, shared_ptr<texture> t1)
	:even(t0), odd(t1)
{};

color checker_texture::value(float u, float v, const point3& p) const {
	auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());

	if (sines < 0) {
		return odd->value(u, v, p);
	}
	else {
		return even->value(u, v, p);
	}
}
