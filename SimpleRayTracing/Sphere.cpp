#include "Sphere.h"
#include <math.h>

Sphere::Sphere() {};

Sphere::Sphere(Vector3 pCenter, float pR, Material *m) {
	radius = pR;
	center = pCenter;
    mat_ptr = m;
}

bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const{
	Vector3 oc = r.origin() - center;
    Vector3 direction = r.direction();
    float a = dot(direction, direction);
    float b = dot(oc, direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float t = (-b - sqrt(b * b - a * c)) / a;
        if (t_min < t && t < t_max) {
            rec.t = t;
            rec.p = r.point_at_parameter(t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }

        t = (-b + sqrt(b * b - a * c)) / a;
        if (t_min < t && t < t_max) {
            rec.t = t;
            rec.p = r.point_at_parameter(t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}