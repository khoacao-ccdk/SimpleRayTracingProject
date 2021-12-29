#ifndef Hitable_H
#define Hitable_H

/*
* Abstract class hitable
* Define the hitable property of the objects that are capable of reflecting light rays off its surface
* A struct hit record is implemented to keep the paths that the light goes through to figure out the resulting light
*/

#include "Vector3.h"
#include "Ray.h"

struct hit_record {
	float t;
	Vector3 p;
	Vector3 normal;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif

