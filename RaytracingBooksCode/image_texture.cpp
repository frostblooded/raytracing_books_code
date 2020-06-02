#include "image_texture.h"
#include "rtw_stb_image.h"

#include <iostream>
#include <algorithm>

using namespace std;

image_texture::image_texture()
	: data(nullptr), width(0), height(0), bytes_per_scanline(0)
{}

image_texture::image_texture(const char* filename) {
	auto components_per_pixel = BYTES_PER_PIXEL;

	data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);

	if (!data) {
		cerr << "ERROR: Could not load texture image file'" << filename << ".\n";
		width = height = 0;
	}

	bytes_per_scanline = BYTES_PER_PIXEL * width;
}

image_texture::~image_texture() {
	delete[] data;
}

color image_texture::value(float u, float v, const point3& p) const {
	if (data == nullptr) {
		return color(0, 1, 1);
	}

	u = clamp(u, 0.0f, 1.0f);
	v = 1 - clamp(v, 0.0f, 1.0f);

	auto i = static_cast<int>(u * width);
	auto j = static_cast<int>(v * height);

	if (i >= width) {
		i = width - 1;
	}

	if (j >= height) {
		j = height - 1;
	}

	const auto color_scale = 1.0 / 255.0;
	auto pixel = data + j * bytes_per_scanline + i * BYTES_PER_PIXEL;

	return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}

