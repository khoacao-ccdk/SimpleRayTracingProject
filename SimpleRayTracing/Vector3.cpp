#include "Vector3.h"
#include <Math.h>

Vector3::Vector3(){
    x = y = z = 0.0f;
}

Vector3::Vector3(float X, float Y, float Z){
    x = X;
    y = Y;
    z = Z;
}

Vector3 Vector3::operator*(float other) const{
    Vector3 result;

    result.x = x * other;
    result.y = y * other;
    result.z = z * other;

    return result;
}

Vector3 Vector3::operator/(float other) const{
    Vector3 result;

    result.x = x / other;
    result.y = y / other;
    result.z = z / other;

    return result;
}

Vector3& Vector3::operator*=(float other){
    Vector3 result;

    x *= other;
    y *= other;
    z *= other;

    return result;
}

Vector3& Vector3::operator/=(float other){
    x /= other;
    y /= other;
    z /= other;

    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const{
    Vector3 result;

    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;

    return result;
}

Vector3 Vector3::operator-(const Vector3& other) const{
    Vector3 result;

    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;

    return result;
}

Vector3 Vector3::operator*(const Vector3& other) const {
    Vector3 result;

    result.x = x * other.x;
    result.y = y * other.y;
    result.z = z * other.z;

    return result;
}

Vector3& Vector3::operator+=(const Vector3& other){
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector3& Vector3::operator*=(const Vector3& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

float Vector3::magnitude(){
    return (float)sqrt((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::normalize(){
    Vector3 result = *this / magnitude();
    return result;
}

float dot(const Vector3& a, const Vector3& b) {
    return (float)(a.x * b.x + a.y * b.y + a.z * b.z);
}

/*

aybz
- azby
azbx
- axbz
axby
- aybx
*/
Vector3 cross(const Vector3& a, const Vector3& b){
    Vector3 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}

Vector3 Bisector(const Vector3& a, const Vector3& b) {
    Vector3 result = a + b;
    return result.normalize();
}