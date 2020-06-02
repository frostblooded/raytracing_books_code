#include "noise_texture.h"

noise_texture::noise_texture() {};

noise_texture::noise_texture(float sc)
	: scale(sc)
{};

color noise_texture::value(float u, float v, const point3& p) const {
	return color(1, 1, 1) * 0.5 * (1.0 + sin(scale * p.z() + 10 * noise.turb(p)));
}
