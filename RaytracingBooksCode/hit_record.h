#ifndef HITRECORDH
#define HITRECORDH

#include "vec3.h"

struct material;

struct hit_record
{
    float t;
    vec3 p;
    vec3 normal;
    material* mat_ptr;
};

#endif
