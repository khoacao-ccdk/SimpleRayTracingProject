// SimpleRayTracing.cpp
// Created by Cody Cao
// Testing Ray Tracing with a simple Ray Tracer
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Sphere.h"
#include "HitableList.h"

using namespace std;

const int WIDTH = 200, HEIGHT = 100;

Vector3 color(const Ray& r, Hitable* world){
    hit_record rec;
    if (world->hit(r, 0.0, numeric_limits<float>::max(), rec)) {
        return Vector3(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1) * 0.5;
    }
    else {
        Vector3 unit_direction = r.direction().normalize();
        float t = unit_direction.y + 1;
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

    Hitable* list[2];
    list[0] = new Sphere(Vector3(0.0f, 0.0f, -1.0f), 0.5);
    list[1] = new Sphere(Vector3(0.0f, -100.5f, -1.0f), 100);
    Hitable* world = new HitableList(list, 2);

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
            Vector3 col = color(r, world);
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
