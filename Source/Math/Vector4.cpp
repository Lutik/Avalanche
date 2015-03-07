#include "stdafx.h"

#include "Vector4.h"

Vector4f::Vector4f(float rx, float ry, float rz, float rw)
{
	x = rx;
	y = ry;
	z = rz;
	w = rw;
}

Vector4f &Vector4f::operator += (const Vector4f &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4f &Vector4f::operator -= (const Vector4f &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4f &Vector4f::operator *= (const float num)
{
	x *= num;
	y *= num;
	z *= num;
	w *= num;
	return *this;
}

Vector4f &Vector4f::operator /= (const float num)
{
	x /= num;
	y /= num;
	z /= num;
	w /= num;
	return *this;
}

Vector4f operator + (const Vector4f &v1, const Vector4f &v2)
{
	return Vector4f( v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w );
}

Vector4f operator - (const Vector4f &v1, const Vector4f &v2)
{
	return Vector4f( v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w );
}

Vector4f operator * (const Vector4f &v, const float num)
{
	return Vector4f( v.x*num, v.y*num, v.z*num, v.w*num );
}

Vector4f operator * (const float num, const Vector4f &v)
{
	return Vector4f( v.x*num, v.y*num, v.z*num, v.w*num );
}

Vector4f operator / (const Vector4f &v, const float num)
{
	return Vector4f( v.x/num, v.y/num, v.z/num, v.w/num );
}

Vector4f operator - (const Vector4f &v)
{
	return Vector4f( -v.x, -v.y, -v.z, -v.w );
}

float Vector4f::Length() const
{
	return std::sqrt(x*x + y*y + z*z + w*w);
}

float Vector4f::Length2() const
{
	return x*x + y*y + z*z + w*w;
}

void Vector4f::Normalize()
{
	float m = 1.0f / std::sqrt(x*x + y*y + z*z +w*w);

	x *= m;
	y *= m;
	z *= m;
	w *= m;
}

float Dot(const Vector4f &vA, const Vector4f &vB)
{
	return (vA.x * vB.x + vA.y * vB.y + vA.z * vB.z + vA.w * vB.w);
}