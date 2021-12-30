#ifndef Camera_H
#define Camera_H

#include "Ray.h"

class Camera{
public:
	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;
	Camera();
	Ray get_ray(float u, float v);
};

#endif

