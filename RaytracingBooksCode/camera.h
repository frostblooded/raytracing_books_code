#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

struct camera
{
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist, float t0 = 0, float t1 = 0);
    ray get_ray(float u, float v);

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;
    float time0, time1;
};

#endif
