#include "Camera.h"

double dRand_Camera() {
	return (double)rand() / RAND_MAX;
}

Vector3 random_in_unit_disk() {
	Vector3 p;
	do {
		p = Vector3(dRand_Camera(), dRand_Camera(), 0.0f) * 2.0f - Vector3(1.0f, 1.0f, 0.0f);
	} while (dot(p, p) >= 1.0f);
	return p;
}

/*
* Camera constructor
* Param: 
* - eye: Camera position
* - spot: Whare the camera is pointing at
* - vUp: up direction in the world coordinate for camera spanning
* - fovY: field of view angle
* - aspect: X / Y ratio
* - aperture, focus_dist: Used to simulate depth of field of a camera
*/
Camera::Camera(Vector3 eye, Vector3 spot, Vector3 vUp, float fovY, float aspect, float aperture, float focus_dist) {
	lens_radius = aperture / 2;
	float theta = fovY * M_PI / 180.0f;
	float halfHeight = tan(theta / 2.0f);
	float halfWidth = aspect * halfHeight;

	origin = eye;
	look = (eye - spot).normalize();
	right = cross(vUp, look).normalize();
	up = cross(look, right).normalize();

	lower_left_corner = origin - right * focus_dist * halfWidth - up * focus_dist * halfHeight - look * focus_dist;
	horizontal = right * halfWidth * focus_dist * 2;
	vertical = up * halfHeight * focus_dist * 2;
}

Ray Camera::get_ray(float s, float t) {
	Vector3 rd = random_in_unit_disk() * lens_radius;
	Vector3 offset = right * rd.x + up * rd.y;
	return Ray(origin + offset, lower_left_corner + horizontal * s + vertical * t - origin - offset);
}