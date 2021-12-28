// SimpleRayTracing.cpp
// Created by Cody Cao
// Testing Ray Tracing with a simple Ray Tracer
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Vector3.h"
#include "Ray.h"

using namespace std;

const int WIDTH = 200, HEIGHT = 100;

float hit_sphear(const Vector3& center, float radius, const Ray& r) {
    Vector3 oc = r.origin() - center;
    Vector3 direction = r.direction();
    float a = dot(direction, direction);
    float b = 2.0f * dot(oc, direction);
    float c = dot(oc, oc) - radius * radius;
    float determination = b * b - 4 * a * c;
    if (determination < 0)
        return -1.0f;
    else
        return (-b - sqrt(determination)) / (2.0f * a);
}

Vector3 color(Ray& r){
    float t = hit_sphear(Vector3(0, 0, -1), 0.5f, r);
    if (t > 0.0f) {
        Vector3 N = (r.point_at_parameter(t) - Vector3(0, 0, -1));
        return Vector3(N.x + 1, N.y + 1, N.z + 1) * 0.5f;
    }
    Vector3 unit_vector = r.direction().normalize();
    t = (float) (0.5 * (unit_vector.y + 1.0));
    return (Vector3(1.0f, 1.0f, 1.0f) * ((1.0f - t))) + (Vector3(0.5f, 0.7f, 1.0f) * t);
}

int main()
{
    Vector3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    Vector3 horizontal(4.0f, 0.0f, 0.0f);
    Vector3 vertical(0.0f, 2.0f, 0.0f);
    Vector3 origin(0.0f, 0.0f, 0.0f);

    //Start writing to PPM file
    ofstream myFile;
    myFile.open("../FrameBuffer.ppm");
    myFile
        << "P3 \n"
        << WIDTH << " " << HEIGHT << "\n"
        << "255 \n";

    for (int j = HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < WIDTH; i++) {
            float u = (float)i / (float)WIDTH;
            float v = (float)j / (float)HEIGHT;
            Ray r(origin, lower_left_corner + horizontal * u + vertical * v);
            Vector3 col = color(r);
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
