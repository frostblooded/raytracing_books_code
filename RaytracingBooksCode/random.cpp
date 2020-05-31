#include "random.h"
#include "vec3.h"

float random()
{
    return rand() / (RAND_MAX + 1.0);
}

float random(float min, float max) {
    return min + (max - min) * random();
}

int random_int(int min, int max) {
    return min + (rand() % (max - min + 1));
}

vec3 random_in_unit_sphere()
{
    while (true) {
        vec3 p = vec3::random_vec(-1, 1);
        if (p.squared_length() >= 1) continue;
        return p;
    }
}

vec3 random_in_unit_disk() {
    vec3 p;

    do {
        p = 2 * vec3(random(), random(), 0) - vec3(1, 1, 0);
    } while (p.squared_length() >= 1);

    return p;
}
