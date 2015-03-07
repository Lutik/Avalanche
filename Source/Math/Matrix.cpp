#include "stdafx.h"

#include "Matrix.h"
#include "Math.h"

void Matrix4f::Transpose()
{
	std::swap(m[1][0], m[0][1]);
	std::swap(m[2][0], m[0][2]);
	std::swap(m[3][0], m[0][3]);
	std::swap(m[2][1], m[1][2]);
	std::swap(m[3][1], m[1][3]);
	std::swap(m[3][2], m[2][3]);
}

Vector4f Matrix4f::GetCol(int col) const
{
	return Vector4f(m[col][0], m[col][1], m[col][2], m[col][3]);
}

Vector4f Matrix4f::GetRow(int row) const
{
	return Vector4f(m[0][row], m[1][row], m[2][row], m[3][row]);
}

Matrix4f& Matrix4f::operator *= (const Matrix4f &other)
{
	*this = *this * other;
	return *this;
}

Matrix4f operator*(const Matrix4f &a,const Matrix4f &b)
{
	Matrix4f mat;
	for(int col = 0; col < 4; ++col)
	{
		for(int row = 0; row < 4; ++row)
		{
			mat.m[col][row] = Dot(a.GetRow(row), b.GetCol(col));
		}
	}
	return mat;
}

Matrix4f Matrix4f::Identity()
{
	Matrix4f mat;
	std::fill(mat.ptr(), mat.ptr()+16, 0.0f);
	mat.m[0][0] = mat.m[1][1] = mat.m[2][2] = mat.m[3][3] = 1.0f;
	return mat;
}

Matrix4f Matrix4f::Translate(Vector3f tv)
{
    Matrix4f m;
    m.m[0][0] = 1.0f; m.m[0][1] = 0.0f; m.m[0][2] = 0.0f; m.m[0][3] = 0.0f;
    m.m[1][0] = 0.0f; m.m[1][1] = 1.0f; m.m[1][2] = 0.0f; m.m[1][3] = 0.0f;
    m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f; m.m[2][3] = 0.0f;
    m.m[3][0] = tv.x; m.m[3][1] = tv.y; m.m[3][2] = tv.z; m.m[3][3] = 1.0f;

    return m;
}

Matrix4f Matrix4f::Scale(Vector3f sv)
{
    Matrix4f m;
    m.m[0][0] = sv.x; m.m[0][1] = 0.0f; m.m[0][2] = 0.0f; m.m[0][3] = 0.0f;
    m.m[1][0] = 0.0f; m.m[1][1] = sv.y; m.m[1][2] = 0.0f; m.m[1][3] = 0.0f;
    m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = sv.z; m.m[2][3] = 0.0f;
    m.m[3][0] = 0.0f; m.m[3][1] = 0.0f; m.m[3][2] = 0.0f; m.m[3][3] = 1.0f;

    return m;
}

Matrix4f Matrix4f::Rotate(float angle, Vector3f v)
{
    v.Normalize();
    float x = v.x;
    float y = v.y;
    float z = v.z;
    float a = Deg2Rad(angle);
    float s = std::sin(a);
    float c = std::cos(a);

    Matrix4f m;
    m.m[0][0] = x*x*(1-c)+c;   m.m[0][1] = x*y*(1-c)-z*s; m.m[0][2] = x*z*(1-c)+y*s; m.m[0][3] = 0.0f;
    m.m[1][0] = x*y*(1-c)+z*s; m.m[1][1] = y*y*(1-c)+c;   m.m[1][2] = y*z*(1-c)-x*s; m.m[1][3] = 0.0f;
    m.m[2][0] = x*z*(1-c)-y*s; m.m[2][1] = y*z*(1-c)+x*s; m.m[2][2] = z*z*(1-c)+c;   m.m[2][3] = 0.0f;
    m.m[3][0] = 0.0f;          m.m[3][1] = 0.0f;          m.m[3][2] = 0.0f;          m.m[3][3] = 1.0f;

    return m;
}

Matrix4f Matrix4f::LookAt(Vector3f eye, Vector3f center, Vector3f up)
{
    Vector3f f = center - eye;
    f.Normalize();

    Vector3f s = Cross(f, up);
    Vector3f u = Cross(s, f);

    Matrix4f M;
    M.m[0][0] = s.x;  M.m[0][1] = u.x;  M.m[0][2] = -f.x; M.m[0][3] = 0.0f;
    M.m[1][0] = s.y;  M.m[1][1] = u.y;  M.m[1][2] = -f.y; M.m[1][3] = 0.0f;
    M.m[2][0] = s.z;  M.m[2][1] = u.z;  M.m[2][2] = -f.z; M.m[2][3] = 0.0f;
    M.m[3][0] = 0.0f; M.m[3][1] = 0.0f; M.m[3][2] = 0.0f; M.m[3][3] = 1.0f;

	return M * Translate(-eye);
}

Matrix4f Matrix4f::Perspective(float fov, float aspect, float zNear, float zFar)
{
    float f = 1.0f / std::tan(Deg2Rad(fov * 0.5f));
    float neg_depth = zNear-zFar;

	Matrix4f m;
    m.m[0][0] = f / aspect; m.m[0][1] = 0.0f; m.m[0][2] = 0.0f;                        m.m[0][3] = 0;
    m.m[1][0] = 0.0f;       m.m[1][1] = f;    m.m[1][2] = 0.0f;                        m.m[1][3] = 0;
    m.m[2][0] = 0.0f;       m.m[2][1] = 0.0f; m.m[2][2] = (zFar + zNear)/neg_depth;    m.m[2][3] = -1.0f; 
    m.m[3][0] = 0.0f;       m.m[3][1] = 0.0f; m.m[3][2] = 2.0f*(zNear*zFar)/neg_depth; m.m[3][3] = 0.0f;

    return m;
}

Matrix4f Matrix4f::Ortho2D(float left, float right, float bottom, float top, float zNear, float zFar)
{
	float rl = right - left;
	float tb = top - bottom;
	float fn = zFar - zNear;

	Matrix4f m;
	m.m[0][0] = 2.0f / rl;        m.m[0][1] = 0.0f;             m.m[0][2] = 0.0f;             m.m[0][3] = 0.0f;
	m.m[1][0] = 0.0f;             m.m[1][1] = 2.0f / tb;        m.m[1][2] = 0.0f;             m.m[1][3] = 0.0f;
	m.m[2][0] = 0.0f;             m.m[2][1] = 0.0f;             m.m[2][2] = 2.0f / fn;        m.m[2][3] = 0.0f;
	m.m[3][0] = -(right+left)/rl; m.m[3][1] = -(top+bottom)/tb; m.m[3][2] = -(zFar+zNear)/fn; m.m[3][3] = 1.0f;

	return m;
}