#include <stdlib.h>

struct vec3;

inline float random();
inline float random(float min, float max);
int random_int(int min, int max);

vec3 random_in_unit_sphere();
vec3 random_in_unit_disk();
