#pragma once

#include "texture.h"

struct checker_texture : public texture
{
	checker_texture();
	checker_texture(shared_ptr<texture> t0, shared_ptr<texture> t1);

	virtual color value(float u, float v, const point3& p) const override;

	shared_ptr<texture> odd;
	shared_ptr<texture> even;
};

