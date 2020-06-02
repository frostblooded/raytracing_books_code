#include <iostream>
#include "image_texture.h"
#include "noise_texture.h"
#include <chrono>
#include "solid_color.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "bvh_node.h"
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
#include "moving_sphere.h"
#include "camera.h"
#include "checker_texture.h"
#include <cfloat>

using namespace std;

hitable_list random_scene() {
    vector<shared_ptr<hitable>> list;

    auto checker = make_shared<checker_texture>(
        make_shared<solid_color>(0.2, 0.3, 0.1),
        make_shared<solid_color>(0.9, 0.9, 0.9)
	);

    auto ground_material = make_shared<lambertian>(checker);
    list.push_back(make_shared<sphere>(vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = random();
            vec3 center(a + 0.9 * random(), 0.2, b + 0.9 * random());

            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    auto albedo = make_shared<solid_color>(color::random_vec() * color::random_vec());
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random(0, 0.5), 0);
                    list.push_back(make_shared<moving_sphere>(center, center2, 0, 1, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    auto albedo = color::random_vec(0.5, 1);
                    auto fuzz = random(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    list.push_back(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    sphere_material = make_shared<dielectric>(1.5);
                    list.push_back(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    list.push_back(make_shared<sphere>(vec3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)));
    list.push_back(make_shared<sphere>(vec3(-4, 1, 0), 1.0, make_shared<lambertian>(make_shared<solid_color>(vec3(0.4, 0.2, 0.1)))));
    list.push_back(make_shared<sphere>(vec3(4, 1, 0), 1.0, make_shared<metal>(vec3(0.7, 0.6, 0.5), 0)));

    return hitable_list(list);
}

vec3 ray_color(const ray& r, bvh_node& world, int depth)
{
    if (depth <= 0) {
        return vec3(0, 0, 0);
    }

    hit_record rec;

    if (world.hit(r, 0.001, FLT_MAX, rec))
    {
        ray scattered;
        color attenuation;

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth - 1);
        }

        return color(0, 0, 0);
    }

    vec3 unit_direction = r.direction().unit_vector();
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1);
}

hitable_list two_spheres() {
    hitable_list objects;

    auto checker = make_shared<checker_texture>(
        make_shared<solid_color>(0.2, 0.3, 0.1),
        make_shared<solid_color>(0.9, 0.9, 0.9)
	);

    objects.add(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<lambertian>(checker)));
    objects.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    return objects;
}

hitable_list two_perlin_spheres() {
    hitable_list objects;

    auto pertext = make_shared<noise_texture>(5);

    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return objects;
}

hitable_list earth() {
    hitable_list objects;

    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);

    auto globe = make_shared<sphere>(point3(0, 0, 0), 2, earth_surface);
    objects.add(globe);

    return objects;
}

int main()
{
    auto t1 = chrono::high_resolution_clock::now();
    srand(time(0));
    ofstream file;
    file.open("test.ppm");

    int image_width = 400;
    int image_height = 300;
    int samples_per_pixel = 100;
    const auto aspect_ratio = float(image_width) / image_height;

    file << "P3\n" << image_width << " " << image_height << "\n255\n";

    //hitable_list objects = random_scene();
    hitable_list objects = earth();
    bvh_node world(objects, 0, 1);
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    float dist_to_focus = 10;
    float aperture = 0.0;
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0, 1);

    for (int j = image_height - 1; j >= 0; j--)
    {
        for (int i = 0; i < image_width; i++)
        {
            vec3 col(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; s++)
            {
                float u = float(i + random()) / float(image_width);
                float v = float(j + random()) / float(image_height);

                ray r = cam.get_ray(u, v);
                col += ray_color(r, world, 50);
            }

            col /= float(samples_per_pixel);
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
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout << "Program execution took " << duration << " milliseconds" << endl;
    return 0;
}

