#include "solid_color.h"

solid_color::solid_color() {}

solid_color::solid_color(color c)
	: color_value(c)
{}

solid_color::solid_color(float red, float green, float blue)
	: solid_color(color(red, green, blue))
{}

color solid_color::value(float u, float v, const vec3& p) const {
	return color_value;
}
