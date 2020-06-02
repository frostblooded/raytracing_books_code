#pragma once

#include "perlin.h"
#include "texture.h"

struct noise_texture : public texture
{
	noise_texture();
	noise_texture(float sc);
	virtual color value(float u, float v, const point3& p) const override;

	perlin noise;
	float scale;
};

