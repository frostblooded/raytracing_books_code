#include "sphere.h"

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    float a = r.direction().squared_length();
    float b = 2.0 * oc.dot(r.direction());
    float c = oc.squared_length() - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        float temp = (-b - sqrt(b * b - a * c)) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }

        temp = (-b + sqrt(b * b - a * c)) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }

    return false;
}
