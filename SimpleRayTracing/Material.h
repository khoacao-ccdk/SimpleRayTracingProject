#ifndef Material_H
#define Material_H

#include "Hitable.h"
#include <stdlib.h>

double dRand() {
    return (double)rand() / RAND_MAX;
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
    r0 *= r0;
    return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

bool refract(const Vector3& v, const Vector3& n, float ni_over_nt, Vector3& refracted) {
    Vector3 uv = v.normalize();
    float dt = dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    if (discriminant > 0.0f) {
        refracted = (uv - n * dt) * ni_over_nt - n * sqrt(discriminant);
        return true;
    }
    else
        return false;
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


/*
* Dielectric class
* Used to represent transparent materials
* The objects with this properties don't reflect lights
*/
class Dielectric : public Material {
public:
    float ref_idx;
    Dielectric(float ri) : ref_idx(ri) {};
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered) const {
        Vector3 outward_normal; 
        Vector3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = Vector3(1.0f, 1.0f, 1.0f);
        Vector3 refracted;
        float reflect_prob; 
        float cosine;

        if (dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal / r_in.direction().magnitude());
        }
        else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0f / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal / r_in.direction().magnitude());
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        }
        else {
            scattered = Ray(rec.p, reflected);
            reflect_prob = 1.0;
        }
        if (dRand() < reflect_prob)
            scattered = Ray(rec.p, reflected);
        else
            scattered = Ray(rec.p, refracted);
        return true;
    }
};

#endif
