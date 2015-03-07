#pragma once

class Vector4f
{
public:
	//data
	float x, y, z, w;

	//constructors
	Vector4f() = default;
	Vector4f(float x, float y, float z, float w);

	//operators
	Vector4f &operator += (const Vector4f &v);
	Vector4f &operator -= (const Vector4f &v);
	Vector4f &operator *= (const float num);
	Vector4f &operator /= (const float num);

	float* ptr() const { return (float*)this; }

	//functions
	float Length() const;
	float Length2() const; //x*x + y*y + z*z + w*w
	void Normalize();
};

Vector4f operator + (const Vector4f &v1, const Vector4f &v2);
Vector4f operator - (const Vector4f &v1, const Vector4f &v2);
Vector4f operator * (const Vector4f &v1, float num);
Vector4f operator * (float num, const Vector4f &v1);
Vector4f operator / (const Vector4f &v1, float num);
Vector4f operator - (const Vector4f &v);

float Dot(const Vector4f &vA, const Vector4f &vB);