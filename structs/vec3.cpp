#include "vec3.h"

ostream &operator<<(ostream &os, const vec3 &vec3)
{
    os << "(" << vec3.x() << ", " << vec3.y() << ", " << vec3.z() << ")";
    return os;
}

vec3 operator*(const float t, const vec3 &v)
{
    return vec3(t * v[0], t * v[1], t * v[2]);
}
