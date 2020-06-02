#include "perlin.h"

perlin::perlin() {
	ranvec = new vec3[POINT_COUNT];

	for (int i = 0; i < POINT_COUNT; i++) {
		ranvec[i] = vec3::random_vec(-1, 1).unit_vector();
	}

	perm_x = perlin_generate_perm();
	perm_y = perlin_generate_perm();
	perm_z = perlin_generate_perm();
}

perlin::~perlin() {
	delete[] ranvec;
	delete[] perm_x;
	delete[] perm_y;
	delete[] perm_z;
}

float perlin::noise(const point3& p) const {
	auto u = p.x() - floor(p.x());
	auto v = p.y() - floor(p.y());
	auto w = p.z() - floor(p.z());

	//u = u * u * (3 - 2 * u);
	//v = v * v * (3 - 2 * v);
	//w = w * w * (3 - 2 * w);

	int i = floor(p.x());
	int j = floor(p.y());
	int k = floor(p.z());

	vec3 c[2][2][2];

	for (int di = 0; di < 2; di++) {
		for (int dj = 0; dj < 2; dj++) {
			for (int dk = 0; dk < 2; dk++) {
				c[di][dj][dk] = ranvec[
					perm_x[(i + di) & 255] ^
					perm_y[(j + dj) & 255] ^
					perm_z[(k + dk) & 255]
				];
			}
		}
	}

	return trilinear_interp(c, u, v, w);
}

int* perlin::perlin_generate_perm() {
	auto p = new int[POINT_COUNT];

	for (int i = 0; i < POINT_COUNT; i++) {
		p[i] = i;
	}

	permute(p, POINT_COUNT);
	return p;
}

void perlin::permute(int* p, int n) {
	for (int i = n - 1; i > 0; i--) {
		int target = random_int(0, i);
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

float perlin::trilinear_interp(vec3 c[2][2][2], float u, float v, float w) {
	auto uu = u * u * (3 - 2 * u);
	auto vv = v * v * (3 - 2 * v);
	auto ww = w * w * (3 - 2 * w);
	auto accum = 0.0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				vec3 weight_v(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu)) *
					(j * vv + (1 - j) * (1 - vv)) *
					(k * ww + (1 - k) * (1 - ww)) *
					c[i][j][k].dot(weight_v);
			}
		}
	}

	return accum;
}

float perlin::turb(const point3& p, int depth) const {
	auto accum = 0.0;
	auto temp_p = p;
	auto weight = 1.0;

	for (int i = 0; i < depth; i++) {
		accum += weight * noise(temp_p);
		weight *= 0.5;
		temp_p *= 2;
	}

	return fabs(accum);
}

