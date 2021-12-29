#ifndef Ray_H
#define Ray_H
#include "Vector3.h"

class Ray{
	Vector3 A;
	Vector3 B;
public:
	Ray();
	Ray(const Vector3& a, const Vector3& b);
	Vector3 origin() const;
	Vector3 direction() const;
	Vector3 point_at_parameter(float t) const;
};

#endif