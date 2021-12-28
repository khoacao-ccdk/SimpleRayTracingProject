#include "Vector3.h"
#include <Math.h>

Vector3::Vector3(){
    x = y = z = w = 0;
}

Vector3::Vector3(float X, float Y, float Z){
    x = X;
    y = Y;
    z = Z;
    w = 0.0f;
}

Vector3 Vector3::operator*(float other){
    Vector3 result;

    result.x = x * other;
    result.y = y * other;
    result.z = z * other;
    result.w = w * other;

    return result;
}

Vector3 Vector3::operator/(float other){
    Vector3 result;

    result.x = x / other;
    result.y = y / other;
    result.z = z / other;
    result.w = w / other;

    return result;
}

Vector3& Vector3::operator*=(float other){
    Vector3 result;

    x *= other;
    y *= other;
    z *= other;
    w *= other;

    return result;
}

Vector3& Vector3::operator/=(float other){
    x /= other;
    y /= other;
    z /= other;
    w /= other;

    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) {
    Vector3 result;

    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;
    result.w = w + other.w;

    return result;
}

Vector3 Vector3::operator-(const Vector3& other) {
    Vector3 result;

    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;
    result.w = w - other.w;

    return result;
}

Vector3& Vector3::operator+=(const Vector3& other){
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

float Vector3::magnitude(){
    return (float)sqrt((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::normalize(){
    Vector3 result = *this / magnitude();
    return result;
}

float dot(Vector3& a, Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/*

aybz
- azby
azbx
- axbz
axby
- aybx
*/
Vector3 cross(Vector3& a, Vector3& b){
    Vector3 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}

Vector3 Bisector(Vector3 a, Vector3 b) {
    return (a + b) / (a + b).magnitude();
}