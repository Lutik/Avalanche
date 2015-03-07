#include "stdafx.h"

#include "Camera.h"
#include "Quaternion.h"

void Camera::SetPerspective(float fov, float aspect, float zNear, float zFar)
{
	mFOV = fov;
	mAspect = aspect;
	mZNear = zNear;
	mZFar = zFar;
}

void Camera::SetPosition(Vector3f pos)
{
	_pos = pos;
}

void Camera::SetUpVector(Vector3f up)
{
	_up = up;
	Vector3f tmp = Cross(_up, _view);
	_up = Cross(_view, tmp);
	_up.Normalize();
}

void Camera::SetViewVector(Vector3f view)
{
	_view = view;
	_view.Normalize();
}

//x,y,z should be components of unit vector
void Camera::RotateViewVec(float x, float y, float z, float angle)
{
	//make rotation quaternion
	float sinA2 = std::sin(angle * 0.5f);
	Quaternion R;
	R.x = x * sinA2;
	R.y = y * sinA2;
	R.z = z * sinA2;
	R.w = std::cos(angle * 0.5f);
	//find new View vector
	Quaternion qView(_view, 0);
	Quaternion tmp = UnitQuatProduct(R, qView);
	qView = UnitQuatProduct(tmp, Conjugate(R));
	_view = qView.v;
}

//x,y,z should be components of unit vector
void Camera::RotateUpVec(float x, float y, float z, float angle)
{
	//make rotation quaternion
	float sinA2 = std::sin(angle * 0.5f);
	Quaternion R;
	R.x = x * sinA2;
	R.y = y * sinA2;
	R.z = z * sinA2;
	R.w = std::cos(angle * 0.5f);
	//find new Up vector
	Quaternion qUp(_up, 0);
	Quaternion tmp = UnitQuatProduct(R, qUp);
	qUp = UnitQuatProduct(tmp, Conjugate(R));
	_up = qUp.v;
}

void Camera::Rotate(float x, float y, float z, float angle)
{
	//make rotation quaternion
	float sinA2 = std::sin(angle * 0.5f);
	Quaternion R;
	R.x = x * sinA2;
	R.y = y * sinA2;
	R.z = z * sinA2;
	R.w = std::cos(angle * 0.5f);
	//find new Up vector
	Quaternion quat1(_up, 0);
	Quaternion tmp = UnitQuatProduct(R, quat1);
	quat1 = UnitQuatProduct(tmp, Conjugate(R));
	_up = quat1.v;
	//find new view vector
	quat1 = Quaternion(_view, 0);
	tmp = UnitQuatProduct(R, quat1);
	quat1 = UnitQuatProduct(tmp, Conjugate(R));
	_view = quat1.v;
}

void Camera::RotateX(float angle)
{
	Vector3f tmp = Cross(_up, _view);
	Rotate(tmp.x, tmp.y, tmp.z, angle);
}

void Camera::RotateY(float angle)
{
	RotateViewVec(_up.x, _up.y, _up.z, angle);
}

void Camera::RotateZ(float angle)
{
	RotateUpVec(_view.x, _view.y, _view.z, angle);	
}

void Camera::MoveForward(float dist)
{
	_pos += _view * dist;
}

void Camera::MoveLeft(float dist)
{
	Vector3f tmp = Cross(_up, _view) * dist;
	_pos += tmp;
}

Matrix4f Camera::GetViewMatrix()
{
	_up.Normalize();
	return Matrix4f::LookAt(_pos, _pos + _view, _up);
}

Matrix4f Camera::GetProjectionMatrix()
{
	return Matrix4f::Perspective(mFOV, mAspect, mZNear, mZFar);
}

