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

const int WIDTH = 200, HEIGHT = 100, S = 100;

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

    Hitable* list[4];
    list[0] = new Sphere(Vector3(0.0f, 0.0f, -1.0f), 0.5, new Lambertian(Vector3(0.8f, 0.3f, 0.3f)));
    list[1] = new Sphere(Vector3(0.0f, -100.5f, -1.0f), 100, new Lambertian(Vector3(0.8f, 0.8f, 0.0f)));
    list[2] = new Sphere(Vector3(1.0f, 0.0f, -1.0f), 0.5, new Metal(Vector3(0.8f, 0.6f, 0.2f), 0.3f));
    list[3] = new Sphere(Vector3(-1.0f, 0.0f, -1.0f), 0.5, new Metal(Vector3(0.8f, 0.8f, 0.8f), 0.1f));
    Hitable* world = new HitableList(list, 4);
    Camera cam;

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
