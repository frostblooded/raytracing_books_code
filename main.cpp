#include <iostream>
#include "vec3.h"

using namespace std;

int main()
{
    int nx = 200;
    int ny = 100;

    cout << "P3\n"
         << nx << " " << ny << "\n255\n";

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
