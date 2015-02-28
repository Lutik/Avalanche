
#include "stdafx.h"
#include "math3d.h"

/************************************************************************
	Matrix4f implementation
************************************************************************/

void Matrix4f::Transpose()
{
	std::swap(m[1], m[4]);
	std::swap(m[2], m[8]);
	std::swap(m[3], m[12]);
	std::swap(m[6], m[9]);
	std::swap(m[7], m[13]);
	std::swap(m[11], m[14]);
}

void Matrix4f::LoadIdentity()
{
	std::fill(m, m+ 16, 0.0f);
    m[0] = 1.0f;
	m[5] = 1.0f;
	m[10] = 1.0f;
	m[15] = 1.0f;
}


float inline Det3(float a11, float a12, float a13,
                   float a21, float a22, float a23,
                   float a31, float a32, float a33)
{
    return a11*(a22*a33 - a32*a23) - a12*(a21*a33 - a23*a31) + a13*(a21*a32-a31*a22);
}

float Matrix4f::Det()
{
    float result = m[0] * Det3(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15])
    - m[1] * Det3(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15])
    + m[2] * Det3(m[4], m[5], m[7], m[8], m[9],  m[11], m[12], m[13], m[15])
    - m[3] * Det3(m[4], m[5], m[6], m[8], m[9],  m[10], m[12], m[13], m[14]);

    return result;
}

Matrix4f QuaternionToMatrix(const Quaternion &quat)
{
    float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
    x2 = quat.x + quat.x;
    y2 = quat.y + quat.y;
    z2 = quat.z + quat.z;
    xx = quat.x * x2;   xy = quat.x * y2;   xz = quat.x * z2;
    yy = quat.y * y2;   yz = quat.y * z2;   zz = quat.z * z2;
    wx = quat.w * x2;   wy = quat.w * y2;   wz = quat.w * z2;

    Matrix4f m;

    m[0]=1.0f-(yy+zz);  m[1]=xy-wz;         m[2]=xz+wy;         m[3]=0;
    m[4]=xy+wz;         m[5]=1.0f-(xx+zz);  m[6]=yz-wx;         m[7]=0;
    m[8]=xz-wy;         m[9]=yz+wx;         m[10]=1.0f-(xx+yy); m[11]=0;
    m[12]=0;            m[13]=0;            m[14]=0;            m[15]=1;

    return m;
}

/************************************************************************
	Deprecated OpenGL functions analogs
************************************************************************/
void Matrix4f::MultMatrix(Matrix4f mult)
{
    Matrix4f mat;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j){
            mat.m[i*4+j] = mult[i*4]*m[j] + mult[i*4+1]*m[4+j] + mult[i*4+2]*m[8+j] + mult[i*4+3]*m[12+j];
		}
    }
	std::copy(mat.m, mat.m + 16, m);
}

void Matrix4f::Perspective(float fov, float aspect,float zNear, float zFar)
{
    // http://www.opengl.org/sdk/docs/man/

    float f = 1.0f / std::tan(Deg2Rad(fov * 0.5f));
    float neg_depth = zNear-zFar;
    Matrix4f m2;

    m2.m[0] = f / aspect;   m2.m[1] = 0;    m2.m[2] = 0;                            m2.m[3] = 0;
    m2.m[4] = 0;            m2.m[5] = f;    m2.m[6] = 0;                            m2.m[7] = 0;
    m2.m[8] = 0;            m2.m[9] = 0;    m2.m[10] = (zFar + zNear)/neg_depth;    m2.m[11] = -1.0f; 
    m2.m[12] = 0;           m2.m[13] = 0;   m2.m[14] = 2.0f*(zNear*zFar)/neg_depth; m2.m[15] = 0.0f;

    MultMatrix(m2);
}

void Matrix4f::Ortho2D(float left, float right, float bottom, float top, float zNear, float zFar)
{
	float rl = right - left;
	float tb = top - bottom;
	float fn = zFar - zNear;

	Matrix4f m2;

	m2.m[0] = 2.0f / rl;         m2.m[1] = 0.0f;              m2.m[2] = 0.0f;              m2.m[3] = 0.0f;
	m2.m[4] = 0.0f;              m2.m[5] = 2.0f / tb;         m2.m[6] = 0.0f;              m2.m[7] = 0.0f;
	m2.m[8] = 0.0f;              m2.m[9] = 0.0f;              m2.m[10] = 2.0f / fn;        m2.m[11] = 0.0f;
	m2.m[12] = -(right+left)/rl; m2.m[13] = -(top+bottom)/tb; m2.m[14] = -(zFar+zNear)/fn; m2.m[15] = 1.0f;

	MultMatrix(m2);
}

void Matrix4f::Translate(float x, float y, float z)
{
    // http://www.opengl.org/sdk/docs/man/

    Matrix4f m2;

    m2.m[0]  = 1.0f; m2.m[1]  = 0;    m2.m[2]  = 0;    m2.m[3]  = 0;
    m2.m[4]  = 0;    m2.m[5]  = 1.0f; m2.m[6]  = 0;    m2.m[7]  = 0;
    m2.m[8]  = 0;    m2.m[9]  = 0;    m2.m[10] = 1.0f; m2.m[11] = 0;
    m2.m[12] = x;    m2.m[13] = y;    m2.m[14] = z;    m2.m[15] = 1.0f;

    MultMatrix(m2);
}

void Matrix4f::Translate(Vector3f tv)
{
    Translate(tv.x, tv.y, tv.z);
}

void Matrix4f::Scale(float x, float y, float z)
{
    // http://www.opengl.org/sdk/docs/man/

    Matrix4f m2;

    m2[0]  = x; m2[1]  = 0; m2[2]  = 0; m2[3]  = 0;
    m2[4]  = 0; m2[5]  = y; m2[6]  = 0; m2[7]  = 0;
    m2[8]  = 0; m2[9]  = 0; m2[10] = z; m2[11] = 0;
    m2[12] = 0; m2[13] = 0; m2[14] = 0; m2[15] = 1;

    MultMatrix(m2);
}

void Matrix4f::Scale(Vector3f sv)
{
    Scale(sv.x, sv.y, sv.z);
}

void Matrix4f::Scale(float s)
{
    Scale(s, s, s);
}

void Matrix4f::Rotate(float angle, float ax, float ay, float az)
{
    Vector3f axe(ax, ay, az);
    Rotate(angle, axe);
}

void Matrix4f::Rotate(float angle, Vector3f axe)
{
    Vector3f v = axe;
    v.Normalize();
    float x = v.x;
    float y = v.y;
    float z = v.z;
    float a = Deg2Rad(angle);
    float s = std::sin(a);
    float c = std::cos(a);
    Matrix4f m2;

    m2[0] = x*x*(1-c)+c;   m2[1] = x*y*(1-c)-z*s; m2[2] = x*z*(1-c)+y*s; m2[3] = 0;
    m2[4] = x*y*(1-c)+z*s; m2[5] = y*y*(1-c)+c;   m2[6] = y*z*(1-c)-x*s; m2[7] = 0;
    m2[8] = x*z*(1-c)-y*s; m2[9] = y*z*(1-c)+x*s; m2[10] = z*z*(1-c)+c;  m2[11] = 0;
    m2[12] = 0;            m2[13] = 0;            m2[14] = 0;            m2[15] = 1;

    MultMatrix(m2);
}

void Matrix4f::LookAt(Vector3f eye, Vector3f center, Vector3f up)
{
    // http://www.opengl.org/sdk/docs/man/

    Vector3f f = center - eye;
    f.Normalize();

    Vector3f s = Cross(f, up);
    Vector3f u = Cross(s, f);

    Matrix4f M;
    M[0] = s.x;   M[1] = u.x;   M[2] = -f.x;   M[3] = 0.0f;
    M[4] = s.y;   M[5] = u.y;   M[6] = -f.y;   M[7] = 0.0f;
    M[8] = s.z;   M[9] = u.z;  M[10] = -f.z; M[11] = 0.0f;
    M[12] = 0.0f; M[13] = 0.0f; M[14] = 0.0f; M[15] = 1.0f;

    MultMatrix(M);
    Translate(-eye); 
}