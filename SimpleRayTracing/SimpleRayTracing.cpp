// SimpleRayTracing.cpp
// Created by Cody Cao
// Testing Ray Tracing with a simple Ray Tracer
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"

using namespace std;

const int WIDTH = 1200, HEIGHT = 800, S = 10;

Vector3 color(const Ray& r, Hitable *world, int depth){
    hit_record rec;
    if (world->hit(r, 0.001, numeric_limits<float>::max(), rec)) {
        Ray scattered;
        Vector3 attenuation;
        
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * color(scattered, world, depth + 1);
        else
            return Vector3(0.0f, 0.0f, 0.0f);
    }
    else {
        Vector3 unit_direction = r.direction().normalize();
        float t = (unit_direction.y + 1.0) * 0.5f;
        return Vector3(1.0f, 1.0f, 1.0f) * (1.0f - t) + Vector3(0.5f, 0.7f, 1.0f) * t;
    }
}

//Construct a dRandom scene with Spheres
Hitable* random_scene() {
    int n = 500;
    Hitable** list = new Hitable * [n + 1];
    list[0] = new Sphere(Vector3(0, -1000, 0), 1000, new Lambertian(Vector3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = dRand();
            Vector3 center(a + 0.9 * dRand(), 0.2, b + 0.9 * dRand());
            if ((center - Vector3(4, 0.2, 0)).magnitude() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new Sphere(
                        center, 0.2,
                        new Lambertian(Vector3(dRand() * dRand(),
                            dRand() * dRand(),
                            dRand() * dRand()))
                    );
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new Sphere(
                        center, 0.2,
                        new Metal(Vector3(0.5 * (1 + dRand()),
                            0.5 * (1 + dRand()),
                            0.5 * (1 + dRand())),
                            0.5 * dRand())
                    );
                }
                else {  // glass
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new Sphere(Vector3(0, 1, 0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vector3(-4, 1, 0), 1.0, new Lambertian(Vector3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vector3(4, 1, 0), 1.0, new Metal(Vector3(0.7, 0.6, 0.5), 0.0));

    return new HitableList(list, i);
}

/*
* Main function
* Include write to PPM functionality to test the ray tracer
*/
int main()
{
    Vector3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    Vector3 horizontal(4.0f, 0.0f, 0.0f);
    Vector3 vertical(0.0f, 2.0f, 0.0f);
    Vector3 origin(0.0f, 0.0f, 0.0f);

    Hitable* world = random_scene();

    //Camera construction
    Vector3 eye(13.0f, 2.0f, 3.0f);
    Vector3 spot(0.0f, 0.0f, 0.0f);
    float distToFocus = 10.0;
    float aperture = 0.1f;
    Camera cam(eye, spot, Vector3(0.0f, 1.0f, 0.0f), 20.0f, float (WIDTH) / float (HEIGHT), aperture, distToFocus);

    //Start writing to PPM file
    ofstream myFile;
    myFile.open("../FrameBuffer.ppm");
    myFile
        << "P3 \n"
        << WIDTH << " " << HEIGHT << "\n"
        << "255 \n";

    for (int j = HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < WIDTH; i++) {
            Vector3 col(0, 0, 0);
            for (int s = 0; s < S; s++) {
                float u = (float)(i + dRand()) / (float)WIDTH;
                float v = (float)(j + dRand()) / (float)HEIGHT;
                Ray r = cam.get_ray(u, v);
                Vector3 p = r.point_at_parameter(2.0f);
                col += color(r, world, 0);
            }
            col /= (float)S;
            col = Vector3(sqrt(col.x), sqrt(col.y), sqrt(col.z));
            myFile 
                << (int)(255.99f * col.x) << " "
                << (int)(255.99f * col.y) << " "
                << (int)(255.99f * col.z) << " ";
        }
        myFile << "\n";
    }
    myFile.close();
    //End writing to PPM file
}
