#include "sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    float a = r.direction().squared_length();
    float b = oc.dot(r.direction());
    float c = oc.squared_length() - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - sqrt(b * b - a * c)) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            get_uv((rec.p - center) / radius, rec.u, rec.v);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }

        temp = (-b + sqrt(b * b - a * c)) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            get_uv((rec.p - center) / radius, rec.u, rec.v);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }
    }

    return false;
}

bool sphere::bounding_box(float t0, float t1, aabb& output_box) const {
    output_box = aabb(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));

    return true;
}

void sphere::get_uv(const vec3& p, float& u, float& v) {
    auto phi = atan2(p.z(), p.x());
    auto theta = asin(p.y());
    u = 1 - (phi + M_PI) / (2 * M_PI);
    v = (theta + M_PI / 2) / M_PI;
}

