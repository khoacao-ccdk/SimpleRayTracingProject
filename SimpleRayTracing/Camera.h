#ifndef Camera_H
#define Camera_H
#define _USE_MATH_DEFINES

#include "Ray.h"
#include <math.h>
#include <random>

class Camera{
public:
	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 look, right, up;
	float lens_radius;
	Camera(Vector3 eye, Vector3 spot, Vector3 vUp, float fovY, float aspect, float aperture, float focus_dist);
	Ray get_ray(float u, float v);
};

Vector3 random_in_unit_disk();

#endif
