#pragma once

#include "vec3.h"

struct texture
{
	virtual color value(float u, float v, const point3& p) const = 0;
};

