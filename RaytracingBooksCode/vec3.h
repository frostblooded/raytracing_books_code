#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <iostream>
#include "random.h"

using namespace std;

struct vec3
{
    vec3() : e{ 0, 0, 0 } {}
    vec3(float e0, float e1, float e2) : e{ e0, e1, e2 } {}

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    inline vec3 operator+(const vec3& v2) const { return vec3(e[0] + v2[0], e[1] + v2[1], e[2] + v2[2]); }
    inline vec3 operator-(const vec3& v2) const { return vec3(e[0] - v2[0], e[1] - v2[1], e[2] - v2[2]); }
    inline vec3 operator*(const vec3& v2) const { return vec3(e[0] * v2[0], e[1] * v2[1], e[2] * v2[2]); }
    inline vec3 operator*(const float f) const { return vec3(e[0] * f, e[1] * f, e[2] * f); }
    inline vec3 operator/(const float f) const { return vec3(e[0] / f, e[1] / f, e[2] / f); }

    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3& v2);
    inline vec3& operator-=(const vec3& v2);
    inline vec3& operator*=(const vec3& v2);
    inline vec3& operator/=(const vec3& v2);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    inline float dot(const vec3& v) const { return e[0] * v[0] + e[1] * v[1] + e[2] * v[2]; }

    inline vec3 cross(const vec3& v) const {
        return vec3(e[1] * v[2] - e[2] * v[1], 
                  -(e[0] * v[2] - e[2] * v[0]),
                    e[0] * v[1] - e[1] * v[0]);
    }

    // Reflect on the surface of the passed in normal vector
    inline vec3 reflect(const vec3& n) const { return *this - 2 * this->dot(n) * n; }

    inline float length() const { return sqrt(squared_length()); }
    inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline vec3 unit_vector() const { return *this / length(); }

    inline static vec3 random_vec() {
        return vec3(random(), random(), random());
    }

    inline static vec3 random_vec(float min, float max) {
        return vec3(random(min, max), random(min, max), random(min, max));
    }

    friend ostream& operator<<(ostream&, const vec3&);
    friend vec3 operator*(const float t, const vec3& v);


    float e[3];
};

inline vec3& vec3::operator+=(const vec3& v2)
{
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3& v2)
{
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const vec3& v2)
{
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3& v2)
{
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3& vec3::operator/=(const float t)
{
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

using point3 = vec3;
using color = vec3;

#endif
