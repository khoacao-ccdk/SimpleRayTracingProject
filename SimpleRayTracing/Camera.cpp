#include "Camera.h"

Camera::Camera() {
	lower_left_corner = Vector3(-2.0f, -1.0f, -1.0f);
	horizontal = Vector3(4.0f, 0.0f, 0.0f);
	vertical = Vector3(0.0f, 2.0f, 0.0f);
	origin = Vector3(0.0f, 0.0f, 0.0f);
}

Ray Camera::get_ray(float u, float v) {
	return Ray(origin, lower_left_corner +  horizontal * u + vertical * v - origin);
}