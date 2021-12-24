#include "Vector3.h"
#include <Math.h>

Vector3::Vector3()
{
    x = y = z = w = 0;
}

Vector3::Vector3(float X, float Y, float Z, float W)
{
    x = X;
    y = Y;
    z = Z;
    w = W;
}

inline Vector3 Vector3::operator*(float other)
{
    Vector3 result;

    result.x = x * other;
    result.y = y * other;
    result.z = z * other;
    result.w = w * other;

    return result;
}

inline Vector3 Vector3::operator/(float other)
{
    Vector3 result;

    result.x = x / other;
    result.y = y / other;
    result.z = z / other;
    result.w = w / other;

    return result;
}

inline Vector3 Vector3::operator+(Vector3& other)
{
    Vector3 result;

    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;
    result.w = w + other.w;

    return result;
}

inline Vector3 Vector3::operator-(Vector3& other)
{
    Vector3 result;

    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;
    result.w = w - other.w;

    return result;
}

inline Vector3 Vector3::operator*=(float other) 
{
    Vector3 result;

    result.x = x * other;
    result.y = y * other;
    result.z = z * other;
    result.w = w * other;

    return result;
}

inline Vector3 Vector3::operator*(float other)
{
    Vector3 result;

    result.x = x / other;
    result.y = y / other;
    result.z = z / other;
    result.w = w / other;

    return result;
}

inline Vector3 Vector3::operator+=(Vector3& other)
{
    Vector3 result;

    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;
    result.w = w + other.w;

    return result;
}

inline Vector3 Vector3::operator-=(Vector3& other)
{
    Vector3 result;

    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;
    result.w = w - other.w;

    return result;
}

inline Vector3 Vector3::operator/=(float other)
{
    Vector3 result;

    result.x = x / other;
    result.y = y / other;
    result.z = z / other;
    result.w = w / other;

    return result;
}

float Vector3::magnitude()
{
    return sqrt((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::normalize()
{
    Vector3 result;

    result.x = x / magnitude();
    result.y = y / magnitude();
    result.z = z / magnitude();
    result.w = w / magnitude();

    return result;
}

inline float Vector3::dot(Vector3& other)
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

/*

aybz
- azby
azbx
- axbz
axby
- aybx
*/
inline Vector3 Vector3::cross(Vector3& other)
{
    Vector3 result;

    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;

    return result;
}

inline Vector3 Bisector(Vector3 a, Vector3 b) {
    return (a + b).normalize();
}