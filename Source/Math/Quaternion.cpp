#include "stdafx.h"

#include "Quaternion.h"
#include "AvMath.h"

Quaternion::Quaternion(float rx, float ry, float rz, float rw)
{
	x = rx;
	y = ry;
	z = rz;
	w = rw;
}

Quaternion::Quaternion(const Vector3f &vec, float rw)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = rw;
}

Quaternion operator-(const Quaternion &quat)
{
	return Quaternion( -quat.v, quat.w );
}

void Quaternion::Normalize()
{
	float m = 1.0f / std::sqrt(x*x + y*y + z*z + w*w);

	x *= m;
	y *= m;
	z *= m;
	w *= m;
}

Quaternion Conjugate(const Quaternion &quat)
{
	return Quaternion(-quat.v, quat.w);
}

Quaternion UnitQuatProduct(const Quaternion &A, const Quaternion &B)
{
	return Quaternion(A.w*B.x + A.x*B.w + A.y*B.z - A.z*B.y,
					A.w*B.y - A.x*B.z + A.y*B.w + A.z*B.x,
					A.w*B.z + A.x*B.y - A.y*B.x + A.z*B.w,
					A.w*B.w - A.x*B.x - A.y*B.y - A.z*B.z);
}

Quaternion QuatProduct(const Quaternion &q1, const Quaternion &q2)
{
    float A, B, C, D, E, F, G, H;

    A = (q1.w + q1.x) * (q2.w + q2.x);
    B = (q1.z - q1.y) * (q2.y - q2.z);
    C = (q1.x - q1.w) * (q2.y + q2.z);
    D = (q1.y + q1.z) * (q2.x - q2.w);
    E = (q1.x + q1.z) * (q2.x + q2.y);
    F = (q1.x - q1.z) * (q2.x - q2.y);
    G = (q1.w + q1.y) * (q2.w - q2.z);
    H = (q1.w - q1.y) * (q2.w + q2.z);

    return Quaternion( A - ( E + F + G + H) * 0.5f,
                       -C + ( E - F + G - H) * 0.5f,
                       -D + ( E - F - G + H) * 0.5f,
                       B + (-E - F + G + H) * 0.5f );
}

Quaternion RotationToQuaternion(Vector3f v, float angle)
{
    v.Normalize();
    float s = std::sin(Deg2Rad(angle * 0.5f));
    float c = std::cos(Deg2Rad(angle * 0.5f));
    return Quaternion(v * s, c);
}