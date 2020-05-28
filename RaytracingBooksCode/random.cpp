#include "random.h"

float random()
{
    return float(rand()) / RAND_MAX;
}

vec3 random_in_unit_sphere()
{
    vec3 p;

    do
    {
        p = 2.0 * vec3(random(), random(), random()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);

    return p;
}
