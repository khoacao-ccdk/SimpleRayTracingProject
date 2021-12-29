#ifndef Sphere_H
#define Sphere_h

#include "Hitable.h"

class Sphere : public Hitable {
public:
	float radius;
	Vector3 center;
	Sphere();
	Sphere(Vector3 pCenter, float pR);
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;
};

#endif


