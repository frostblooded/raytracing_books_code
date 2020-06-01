#pragma once

#include "texture.h"

struct solid_color : public texture
{
	solid_color();
	solid_color(color c);
	solid_color(float red, float green, float blue);

	virtual color value(float u, float v, const vec3& p) const;

private:
	color color_value;
};

