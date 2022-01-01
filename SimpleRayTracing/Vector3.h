/*
* Vector class
* Used to store 3D Vector, including x, y, z, and homogenous coordinates
*/
#ifndef Vector3_H
#define Vector3_H

struct Vector3 {
	float x, y, z;

	Vector3();
	Vector3(float X, float Y, float Z);
	Vector3 operator-() const;

	Vector3 operator*(float other) const;
	Vector3 operator/(float other) const;
	Vector3& operator*=(float other);
	Vector3& operator/=(float other);

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(const Vector3& other);

	float magnitude() const;
	Vector3 normalize() const;
	
};

float dot(const Vector3& a, const Vector3& b);
Vector3 cross(const Vector3& a, const Vector3& b);
inline Vector3 Bisector(const Vector3& a, const Vector3& b);

#endif
