#pragma once

class Vector2f
{
public:
	//data
	float x, y;

	//constructors
	Vector2f() = default;
	Vector2f(float x, float y);

	//operators
	Vector2f &operator += (const Vector2f &v);
	Vector2f &operator -= (const Vector2f &v);
	Vector2f &operator *= (const float num);
	Vector2f &operator /= (const float num);

	float* ptr() { return (float*)this; }

	//functions
	float Length() const;
	float Length2() const; //x*x + y*y
	void Normalize();
};

Vector2f operator + (const Vector2f &v1, const Vector2f &v2);
Vector2f operator - (const Vector2f &v1, const Vector2f &v2);
Vector2f operator * (const Vector2f &v1, float num);
Vector2f operator * (float num, const Vector2f &v1);
Vector2f operator / (const Vector2f &v1, float num);
Vector2f operator - (const Vector2f &v);

float Dot(const Vector2f &vA, const Vector2f &vB);