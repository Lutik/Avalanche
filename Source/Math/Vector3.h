#pragma once

class Vector3f
{
public:
	//data
	float x, y, z;

	//constructors
	Vector3f() = default;
	Vector3f(float x, float y, float z);

	//operators
	Vector3f &operator += (const Vector3f &v);
	Vector3f &operator -= (const Vector3f &v);
	Vector3f &operator *= (float num);
	Vector3f &operator /= (float num);

	float* ptr() const { return (float*)this; }

	//functions
	float Length() const;
	float Length2() const; //x*x + y*y + z*z
	void Normalize();
};

Vector3f operator + (const Vector3f &v1, const Vector3f &v2);
Vector3f operator - (const Vector3f &v1, const Vector3f &v2);
Vector3f operator * (const Vector3f &v1, float num);
Vector3f operator * (float num, const Vector3f &v1);
Vector3f operator / (const Vector3f &v1, float num);
Vector3f operator - (const Vector3f &v);

Vector3f Cross(const Vector3f &vA, const Vector3f &vB);
float Dot(const Vector3f &vA, const Vector3f &vB);