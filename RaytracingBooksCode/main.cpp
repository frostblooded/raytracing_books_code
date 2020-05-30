#include <iostream>
#define _USE_MATH_DEFINES
#include "math.h"
#include <fstream>
#include <time.h>
#include "random.h"
#include "lambertian.h"
#include "dielectric.h"
#include "metal.h"
#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include <cfloat>

using namespace std;

hitable* random_scene() {
    int n = 500;
    hitable** list = new hitable * [n + 1];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));

    int i = 1;

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = random();
            vec3 center(a + 0.9 * random(), 0.2, b + 0.9 * random());

            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(random() * random(), random() * random(), random() * random())));
                }
                else if (choose_mat < 0.95) {
                    list[i++] = new sphere(center, 0.2, new metal(vec3(0.5 * (1 + random()), 0.5 * (1 + random()), 0.5 * (1 + random())), 0.5 * random()));
                }
                else {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0));

    return new hitable_list(list, i);
}

vec3 ray_color(const ray& r, hitable* world, int depth)
{
    hit_record rec;

    if (world->hit(r, 0.001, FLT_MAX, rec))
    {
        ray scattered;
        vec3 attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth + 1);
        }

        return vec3(0, 0, 0);
    }

    vec3 unit_direction = r.direction().unit_vector();
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1);
}

int main()
{
    srand(time(0));
    ofstream file;
    file.open("test.ppm");

    int nx = 1200;
    int ny = 800;
    int ns = 10;

    file << "P3\n" << nx << " " << ny << "\n255\n";

    hitable* world = random_scene();
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10;
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);

            for (int s = 0; s < ns; s++)
            {
                float u = float(i + random()) / float(nx);
                float v = float(j + random()) / float(ny);

                ray r = cam.get_ray(u, v);
                col += ray_color(r, world, 0);
            }

            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());

            file << ir << " " << ig << " " << ib << "\n";
        }

        if (j % 25 == 0) {
			cout << j << " rows left" << endl;
        }
    }

    file.close();
    return 0;
}

