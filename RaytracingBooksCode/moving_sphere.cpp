#include "moving_sphere.h"

moving_sphere::moving_sphere() {}

moving_sphere::moving_sphere(point3 cen0, point3 cen1, float t0, float t1, float r, shared_ptr<material> m)
	: center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m)
{}

bool moving_sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center(r.time());
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
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-b + sqrt(b * b - a * c)) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}

point3 moving_sphere::center(float time) const {
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}


bool moving_sphere::bounding_box(float t0, float t1, aabb& output_box) const {
    aabb box0(
        center(t0) - vec3(radius, radius, radius),
        center(t0) + vec3(radius, radius, radius));
    aabb box1(
        center(t1) - vec3(radius, radius, radius),
        center(t1) + vec3(radius, radius, radius));

    output_box = hitable::surrounding_box(box0, box1);
    return true;
}

