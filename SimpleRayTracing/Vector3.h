/*
* Vector class
* Used to store 3D Vector, including x, y, z, and homogenous coordinates
*/
#ifndef Vector3_H
#define Vector3_H

struct Vector3 {
	float x, y, z, w;

	Vector3();
	Vector3(float X, float Y, float Z, float W);
	inline Vector3 operator*(float other);
	inline Vector3 operator/(float other);
	inline Vector3 operator+(Vector3& other);
	inline Vector3 operator-(Vector3& other);
	inline Vector3 operator+=(Vector3& other);
	inline Vector3 operator-=(Vector3& other);
	inline Vector3 operator*=(float other);
	inline Vector3 operator/=(float other);
	inline float magnitude();
	inline float dot(Vector3& other);
	inline Vector3 normalize();
	inline Vector3 cross(Vector3& other);
};

inline Vector3 Bisector(Vector3 a, Vector3 b);

#endif
