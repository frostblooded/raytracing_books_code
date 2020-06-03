#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include "hit_record.h"
#include "aabb.h"
#define _USE_MATH_DEFINES
#include "math.h"

struct hitable
{
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const = 0;

    static aabb surrounding_box(aabb box0, aabb box1);

    inline static float degrees_to_radians(float degrees) {
        return degrees * M_PI / 180;
    }
};

#endif
