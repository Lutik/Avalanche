#include "stdafx.h"

#include "Vector2.h"

Vector2f::Vector2f(float rx, float ry)
{
	x = rx;
	y = ry;
}

Vector2f &Vector2f::operator += (const Vector2f &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2f &Vector2f::operator -= (const Vector2f &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2f &Vector2f::operator *= (const float num)
{
	x *= num;
	y *= num;
	return *this;
}

Vector2f &Vector2f::operator /= (const float num)
{
	x /= num;
	y /= num;
	return *this;
}

Vector2f operator + (const Vector2f &v1, const Vector2f &v2)
{
	return Vector2f( v1.x+v2.x, v1.y+v2.y);
}

Vector2f operator - (const Vector2f &v1, const Vector2f &v2)
{
	return Vector2f( v1.x-v2.x, v1.y-v2.y);
}

Vector2f operator * (const Vector2f &v, float num)
{
	return Vector2f( v.x*num, v.y*num);
}

Vector2f operator * (float num, const Vector2f &v)
{
	return Vector2f( v.x*num, v.y*num);
}

Vector2f operator / (const Vector2f &v, float num)
{
	return Vector2f( v.x/num, v.y/num );
}

Vector2f operator - (const Vector2f &v)
{
	return Vector2f( -v.x, -v.y );
}

float Vector2f::Length() const
{
	return std::sqrt(x*x + y*y);
}

float Vector2f::Length2() const
{
	return x*x + y*y;
}

void Vector2f::Normalize()
{
	float m = 1.0f / std::sqrt(x*x + y*y);

	x *= m;
	y *= m;
}

float Dot(const Vector2f &vA, const Vector2f &vB)
{
	return (vA.x*vB.x + vA.y*vB.y);
}