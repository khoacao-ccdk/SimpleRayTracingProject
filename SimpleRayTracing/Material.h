#ifndef Material_H
#define Material_H

#include "Hitable.h"
#include <stdlib.h>

double dRand() {
    return (double)rand() / RAND_MAX;
}

//Return a point that lies within the unit sphere
Vector3 random_point_in_unit_sphere() {
    Vector3 p;
    do {
        p = Vector3(dRand(), dRand(), dRand()) * 2.0f - Vector3(1.0f, 1.0f, 1.0f);
    } while (p.magnitude() >= 1.0f);
    return p;
}

Vector3 reflect(const Vector3& v, const Vector3& n) {
    return v - n * dot(v, n) * 2.0f;
}

class Material {
public:
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
    Vector3 albedo;
    Lambertian(const Vector3& a) : albedo(a) {};
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) const {
        Vector3 target = rec.p + rec.normal + random_point_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
};

class Metal : public Material {
public:
    Vector3 albedo;
    float fuzz;
    Metal(const Vector3& a, float f) : albedo(a) { fuzz = (f < 1) ? f : 1.0f; };
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) const {
        Vector3 reflected = reflect(r_in.direction().normalize(), rec.normal);
        scattered = Ray(rec.p, reflected + random_point_in_unit_sphere() * fuzz);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};

#endif
