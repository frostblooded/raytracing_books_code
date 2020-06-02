#pragma once

#include "vec3.h"

struct perlin
{
	perlin();
	~perlin();

	float noise(const point3& p) const;
	float turb(const point3& p, int depth = 7) const;

private:
	static const int POINT_COUNT = 256;

	vec3* ranvec;
	int* perm_x;
	int* perm_y;
	int* perm_z;

	static int* perlin_generate_perm();
	static void permute(int* p, int n);
	static inline float trilinear_interp(vec3 c[2][2][2], float u, float v, float w);
};

