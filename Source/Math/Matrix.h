#pragma once

#include "Vector3.h"
#include "Vector4.h"

class Matrix4f
{
public:
	float m[4][4];

	void Transpose();
	Vector4f GetCol(int col) const;
	Vector4f GetRow(int row) const;

	Matrix4f& operator *= (const Matrix4f &other);

	float* ptr() const { return (float*)this; }

	// конструирование типичных разновидностей матриц
	static Matrix4f Identity();
	static Matrix4f Translate(Vector3f tv);
	static Matrix4f Scale(Vector3f sv);
	static Matrix4f Rotate(float angle, Vector3f axe);
	static Matrix4f LookAt(Vector3f eye, Vector3f center, Vector3f up);
	static Matrix4f Perspective(float fov, float aspect, float zNear, float zFar);
	static Matrix4f Ortho2D(float left, float right, float bottom, float top, float zNear, float zFar);
};

Matrix4f operator*(const Matrix4f &a, const Matrix4f &b);