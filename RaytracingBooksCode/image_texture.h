#pragma once

#include "texture.h"

struct image_texture : public texture {
	const static int BYTES_PER_PIXEL = 3;

	image_texture();
	image_texture(const char* filename);
	~image_texture();

	virtual color value(float u, float v, const point3& p) const override;

private:
	unsigned char* data;
	int width, height;
	int bytes_per_scanline;
};
