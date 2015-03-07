#include "stdafx.h"

#include "Vector3.h"

Vector3f::Vector3f(float rx, float ry, float rz)
{
	x = rx;
	y = ry;
	z = rz;
}

Vector3f &Vector3f::operator += (const Vector3f &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3f &Vector3f::operator -= (const Vector3f &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3f &Vector3f::operator *= (float num)
{
	x *= num;
	y *= num;
	z *= num;
	return *this;
}

Vector3f &Vector3f::operator /= (float num)
{
	x /= num;
	y /= num;
	z /= num;
	return *this;
}

Vector3f operator + (const Vector3f &v1, const Vector3f &v2)
{
	return Vector3f( v1.x+v2.x, v1.y+v2.y, v1.z+v2.z );
}

Vector3f operator - (const Vector3f &v1, const Vector3f &v2)
{
	return Vector3f( v1.x-v2.x, v1.y-v2.y, v1.z-v2.z );
}

Vector3f operator * (const Vector3f &v, float num)
{
	return Vector3f( v.x*num, v.y*num, v.z*num );
}

Vector3f operator * (float num, const Vector3f &v)
{
	return Vector3f( v.x*num, v.y*num, v.z*num );
}

Vector3f operator / (const Vector3f &v, float num)
{
	return Vector3f( v.x/num, v.y/num, v.z/num );
}

Vector3f operator - (const Vector3f &v)
{
	return Vector3f( -v.x, -v.y, -v.z );
}

float Vector3f::Length() const
{
	return std::sqrt(x*x + y*y + z*z);
}

float Vector3f::Length2() const
{
	return x*x + y*y + z*z;
}

void Vector3f::Normalize()
{
	float m = 1.0f / std::sqrt(x*x + y*y + z*z);

	x *= m;
	y *= m;
	z *= m;
}

Vector3f Cross(const Vector3f &vA, const Vector3f &vB)
{
	return Vector3f(vA.y*vB.z - vA.z*vB.y,
					vA.z*vB.x - vA.x*vB.z,
					vA.x*vB.y - vA.y*vB.x);
}

float Dot(const Vector3f &vA, const Vector3f &vB)
{
	return (vA.x*vB.x + vA.y*vB.y + vA.z*vB.z);
}
