#ifndef HITRECORDH
#define HITRECORDH

#include "vec3.h"

struct hit_record
{
    float t;
    vec3 p;
    vec3 normal;
};

#endif
