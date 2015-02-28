#ifndef MATH3D_HEADER_INCLUDED_
#define MATH3D_HEADER_INCLUDED_

/************************************************************************
Math3D Library

Author: Shageev R.R. (share@list.ru)
2007-2015
************************************************************************/

/************************************************************************
	Small functions, mathematical constants
************************************************************************/

namespace math
{
	const float PI = 3.141592653589793f;
}

inline float Deg2Rad(float angle)
{
    return angle * 0.017453292519943f;
}

inline float Rad2Deg(float angle)
{
    return angle * 57.295779513082321f;
}

/************************************************************************
	Vector classes
************************************************************************/

class Vector3f
{
public:
	//data
	float x, y, z;
	//constructors
	Vector3f() = default;
	Vector3f(float x, float y, float z);
	//operators
	const Vector3f &operator += (const Vector3f &v);
	const Vector3f &operator -= (const Vector3f &v);
	const Vector3f &operator *= (const float num);
	const Vector3f &operator /= (const float num);

	friend Vector3f operator+(const Vector3f &v1, const Vector3f &v2);
	friend Vector3f operator-(const Vector3f &v1, const Vector3f &v2);
	friend Vector3f operator*(const Vector3f &v1, const float num);
	friend Vector3f operator*(const float num, const Vector3f &v1);
	friend Vector3f operator/(const Vector3f &v1, const float num);
	friend Vector3f operator-(const Vector3f &v);

	float* ptr() { return (float*)this; }

	//functions
	float Length() const;
	float Length2() const; //x*x + y*y + z*z
	void Normalize();
};

Vector3f Cross(const Vector3f &vA, const Vector3f &vB);
float Dot(const Vector3f &vA, const Vector3f &vB);

/////////////////////////////////////////////////////////////////////////

class Vector2f
{
public:
	//data
	float x, y;
	//constructors
	Vector2f() = default;
	Vector2f(float x, float y);
	//operators
	const Vector2f &operator += (const Vector2f &v);
	const Vector2f &operator -= (const Vector2f &v);
	const Vector2f &operator *= (const float num);
	const Vector2f &operator /= (const float num);

	friend Vector2f operator+(const Vector2f &v1, const Vector2f &v2);
	friend Vector2f operator-(const Vector2f &v1, const Vector2f &v2);
	friend Vector2f operator*(const Vector2f &v1, const float num);
	friend Vector2f operator*(const float num, const Vector2f &v1);
	friend Vector2f operator/(const Vector2f &v1, const float num);
	friend Vector2f operator-(const Vector2f &v);

	float* ptr() { return (float*)this; }

	//functions
	float Length() const;
	float Length2() const; //x*x + y*y
	void Normalize();
};

float Dot(const Vector2f &vA, const Vector2f &vB);

/////////////////////////////////////////////////////////////////////////

class Vector4f
{
public:
	//data
	float x, y, z, w;
	//constructors
	Vector4f() = default;
	Vector4f(float x, float y, float z, float w);
	//operators
	const Vector4f &operator += (const Vector4f &v);
	const Vector4f &operator -= (const Vector4f &v);
	const Vector4f &operator *= (const float num);
	const Vector4f &operator /= (const float num);

	friend Vector4f operator+(const Vector4f &v1, const Vector4f &v2);
	friend Vector4f operator-(const Vector4f &v1, const Vector4f &v2);
	friend Vector4f operator*(const Vector4f &v1, const float num);
	friend Vector4f operator*(const float num, const Vector4f &v1);
	friend Vector4f operator/(const Vector4f &v1, const float num);
	friend Vector4f operator-(const Vector4f &v);

	float* ptr() { return (float*)this; }
	//functions
	float Length() const;
	float Length2() const; //x*x + y*y + z*z + w*w
	void Normalize();
};

/************************************************************************
	Quaternions
************************************************************************/

class Quaternion
{
public:
	//data
	union{
		struct{ 
			float x,y,z,w;
		};
		struct{
			Vector3f v;
			float w;
		};
	};
	//constructors
	Quaternion() = default;
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3f &vec, float w);

	friend Quaternion operator-(const Quaternion &quat); //works as Conjugate
    friend Quaternion operator*(const Quaternion &q1, const Quaternion &q2); //unit quaternion product
	//functions
	void Normalize();
};

Quaternion RotationToQuaternion(float x, float y, float z, float angle);
Quaternion Conjugate(const Quaternion &quat);
Quaternion UnitQuatProduct(const Quaternion &A, const Quaternion &B);
Quaternion QuatProduct(const Quaternion &A, const Quaternion &B);

/************************************************************************
	Matrices
************************************************************************/

class Matrix4f
{
public:
	//data
	float m[16];

	//operators
    inline float &operator [] (int idx)  { return m[idx]; }
	//functions
	float Det(); //determinant
	void Transpose();
	void LoadIdentity();

	float* ptr() { return (float*)this; }

    // deprecated OpenGL matrix functions analogs
    void MultMatrix(Matrix4f mult);
    void Perspective(float fov, float aspect,float zNear, float zFar);
	void Ortho2D(float left, float right, float bottom, float top, float zNear, float zFar);
    void Translate(float x, float y, float z);
    void Translate(Vector3f tv);
    void Scale(float x, float y, float z);
    void Scale(Vector3f sv);
    void Scale(float s);
    void Rotate(float angle, float x, float y, float z);
    void Rotate(float angle, Vector3f axe);
    void LookAt(Vector3f eye, Vector3f center, Vector3f up);
};

Matrix4f QuaternionToMatrix(const Quaternion &Q);

//Random
float randf();

#endif //MATH3D_HEADER_INCLUDED_