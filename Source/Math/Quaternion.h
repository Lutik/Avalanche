#pragma once

#include "Vector3.h"
#include "Matrix.h"

class Quaternion
{
public:
	//data
	union{
		struct { 
			float x,y,z,w;
		};
		struct {
			Vector3f v;
			float w;
		};
	};

	//constructors
	Quaternion() = default;
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Vector3f &vec, float w);

	//operators
	friend Quaternion operator-(const Quaternion &quat); //works as Conjugate

	//functions
	void Normalize();
};

Quaternion RotationToQuaternion(Vector3f v, float angle);
Quaternion Conjugate(const Quaternion &quat);
Quaternion UnitQuatProduct(const Quaternion &A, const Quaternion &B);
Quaternion QuatProduct(const Quaternion &A, const Quaternion &B);
Matrix4f RotationMatrix(const Quaternion &quat);
Vector3f RotateVector(Vector3f vec, const Quaternion &quat);
Quaternion RotationFromVectors(Vector3f from, Vector3f to);