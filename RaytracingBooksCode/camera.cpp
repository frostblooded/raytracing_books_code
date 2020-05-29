#include "camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "random.h"

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
{
	lens_radius = aperture / 2;
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	origin = lookfrom;
	w = (lookfrom - lookat).unit_vector();
	u = vup.cross(w).unit_vector();
	v = w.cross(u);
	lower_left_corner = origin - half_width * focus_dist * u - focus_dist * half_height * v - focus_dist * w;
	horizontal = 2 * half_width * focus_dist * u;
	vertical = 2 * half_height * focus_dist * v;
}

ray camera::get_ray(float s, float t)
{
	vec3 rd = lens_radius * random_in_unit_disk();
	vec3 offset = u * rd.x() + v * rd.y();
	return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}
