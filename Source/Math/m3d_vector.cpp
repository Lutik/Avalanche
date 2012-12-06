
#include "stdafx.h"
#include "math3d.h"

/************************************************************************
	Vector3f implementation
************************************************************************/
Vector3f::Vector3f()
{
	//x = y = z = 0.0f;
}

Vector3f::Vector3f(const Vector3f &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector3f::Vector3f(float rx, float ry, float rz)
{
	x = rx;
	y = ry;
	z = rz;
}

const Vector3f &Vector3f::operator = (const Vector3f &v)
{
	if( this != &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	return *this;
}

const Vector3f &Vector3f::operator += (const Vector3f &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

const Vector3f &Vector3f::operator -= (const Vector3f &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

const Vector3f &Vector3f::operator *= (const float num)
{
	x *= num;
	y *= num;
	z *= num;
	return *this;
}

const Vector3f &Vector3f::operator /= (const float num)
{
	x /= num;
	y /= num;
	z /= num;
	return *this;
}

Vector3f operator+(const Vector3f &v1, const Vector3f &v2)
{
	return Vector3f( v1.x+v2.x, v1.y+v2.y, v1.z+v2.z );
}

Vector3f operator-(const Vector3f &v1, const Vector3f &v2)
{
	return Vector3f( v1.x-v2.x, v1.y-v2.y, v1.z-v2.z );
}

Vector3f operator*(const Vector3f &v, const float num)
{
	return Vector3f( v.x*num, v.y*num, v.z*num );
}

Vector3f operator*(const float num, const Vector3f &v)
{
	return Vector3f( v.x*num, v.y*num, v.z*num );
}

Vector3f operator/(const Vector3f &v, const float num)
{
	return Vector3f( v.x/num, v.y/num, v.z/num );
}

Vector3f operator-(const Vector3f &v)
{
	return Vector3f( -v.x, -v.y, -v.z );
}

float Vector3f::Length() const
{
	return sqrt(x*x + y*y + z*z);
}

float Vector3f::Length2() const
{
	return x*x + y*y + z*z;
}

void Vector3f::Normalize()
{
	float m = 1.0f / sqrt(x*x + y*y + z*z);

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

/************************************************************************
	Vector2f implementation
************************************************************************/
Vector2f::Vector2f()
{
	//x = y = 0.0f;
}

Vector2f::Vector2f(const Vector2f &vec)
{
	x = vec.x;
	y = vec.y;
}

Vector2f::Vector2f(float rx, float ry)
{
	x = rx;
	y = ry;
}

const Vector2f &Vector2f::operator = (const Vector2f &v)
{
	if( this != &v)
	{
		x = v.x;
		y = v.y;
	}
	return *this;
}

const Vector2f &Vector2f::operator += (const Vector2f &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

const Vector2f &Vector2f::operator -= (const Vector2f &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

const Vector2f &Vector2f::operator *= (const float num)
{
	x *= num;
	y *= num;
	return *this;
}

const Vector2f &Vector2f::operator /= (const float num)
{
	x /= num;
	y /= num;
	return *this;
}

Vector2f operator+(const Vector2f &v1, const Vector2f &v2)
{
	return Vector2f( v1.x+v2.x, v1.y+v2.y);
}

Vector2f operator-(const Vector2f &v1, const Vector2f &v2)
{
	return Vector2f( v1.x-v2.x, v1.y-v2.y);
}

Vector2f operator*(const Vector2f &v, const float num)
{
	return Vector2f( v.x*num, v.y*num);
}

Vector2f operator*(const float num, const Vector2f &v)
{
	return Vector2f( v.x*num, v.y*num);
}

Vector2f operator/(const Vector2f &v, const float num)
{
	return Vector2f( v.x/num, v.y/num );
}

Vector2f operator-(const Vector2f &v)
{
	return Vector2f( -v.x, -v.y );
}

float Vector2f::Length() const
{
	return sqrtf(x*x + y*y);
}

float Vector2f::Length2() const
{
	return x*x + y*y;
}

void Vector2f::Normalize()
{
	float m = 1.0f / sqrtf(x*x + y*y);

	x *= m;
	y *= m;
}

float DotProduct2f(const Vector2f &vA, const Vector2f &vB)
{
	return (vA.x*vB.x + vA.y*vB.y);
}

/************************************************************************
	Vector4f implementation
************************************************************************/
Vector4f::Vector4f()
{
	//x = y = z = w = 0.0f;
}

Vector4f::Vector4f(const Vector4f &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

Vector4f::Vector4f(float rx, float ry, float rz, float rw)
{
	x = rx;
	y = ry;
	z = rz;
	w = rw;
}

const Vector4f &Vector4f::operator = (const Vector4f &v)
{
	if( this != &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	return *this;
}

const Vector4f &Vector4f::operator += (const Vector4f &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

const Vector4f &Vector4f::operator -= (const Vector4f &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

const Vector4f &Vector4f::operator *= (const float num)
{
	x *= num;
	y *= num;
	z *= num;
	w *= num;
	return *this;
}

const Vector4f &Vector4f::operator /= (const float num)
{
	x /= num;
	y /= num;
	z /= num;
	w /= num;
	return *this;
}

Vector4f operator+(const Vector4f &v1, const Vector4f &v2)
{
	return Vector4f( v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w );
}

Vector4f operator-(const Vector4f &v1, const Vector4f &v2)
{
	return Vector4f( v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w );
}

Vector4f operator*(const Vector4f &v, const float num)
{
	return Vector4f( v.x*num, v.y*num, v.z*num, v.w*num );
}

Vector4f operator*(const float num, const Vector4f &v)
{
	return Vector4f( v.x*num, v.y*num, v.z*num, v.w*num );
}

Vector4f operator/(const Vector4f &v, const float num)
{
	return Vector4f( v.x/num, v.y/num, v.z/num, v.w/num );
}

Vector4f operator-(const Vector4f &v)
{
	return Vector4f( -v.x, -v.y, -v.z, -v.w );
}

float Vector4f::Length() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

float Vector4f::Length2() const
{
	return x*x + y*y + z*z + w*w;
}

void Vector4f::Normalize()
{
	float m = 1.0f / sqrt(x*x + y*y + z*z +w*w);

	x *= m;
	y *= m;
	z *= m;
	w *= m;
}