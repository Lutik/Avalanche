#include "stdafx.h"
#include "Camera.h"
#include "Renderer.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

void CCamera::SetPerspective(float fov, float aspect, float zNear, float zFar)
{
	mFOV = fov;
	mAspect = aspect;
	mZNear = zNear;
	mZFar = zFar;
}

void CCamera::SetUpVector(float x, float y, float z)
{
	mUp.x = x;
	mUp.y = y;
	mUp.z = z;
	Vector3f tmp = CrossProduct3f(mUp, mView);
	mUp = CrossProduct3f(mView, tmp);
	mUp.Normalize();
}

void CCamera::SetViewVector(float x, float y, float z)
{
	mView.x = x;
	mView.y = y;
	mView.z = z;
	mView.Normalize();
}

//x,y,z should be components of unit vector
void CCamera::RotateViewVec(float x, float y, float z, float angle)
{
	//make rotation quaternion
	float sinA2 = sinf(angle/2);
	Quaternion R;
	R.x = x * sinA2;
	R.y = y * sinA2;
	R.z = z * sinA2;
	R.w = cosf(angle/2);
	//find new View vector
	Quaternion qView(mView, 0);
	Quaternion tmp = UnitQuatProduct(R, qView);
	qView = UnitQuatProduct(tmp, Conjugate(R));
	mView = qView.v;
}

//x,y,z should be components of unit vector
void CCamera::RotateUpVec(float x, float y, float z, float angle)
{
	//make rotation quaternion
	float sinA2 = sinf(angle/2);
	Quaternion R;
	R.x = x * sinA2;
	R.y = y * sinA2;
	R.z = z * sinA2;
	R.w = cosf(angle/2);
	//find new Up vector
	Quaternion qUp(mUp, 0);
	Quaternion tmp = UnitQuatProduct(R, qUp);
	qUp = UnitQuatProduct(tmp, Conjugate(R));
	mUp = qUp.v;
}

void CCamera::Rotate(float x, float y, float z, float angle)
{
	//make rotation quaternion
	float sinA2 = sinf(angle/2);
	Quaternion R;
	R.x = x * sinA2;
	R.y = y * sinA2;
	R.z = z * sinA2;
	R.w = cosf(angle/2);
	//find new Up vector
	Quaternion quat1(mUp, 0);
	Quaternion tmp = UnitQuatProduct(R, quat1);
	quat1 = UnitQuatProduct(tmp, Conjugate(R));
	mUp = quat1.v;
	//find new view vector
	quat1 = Quaternion(mView, 0);
	tmp = UnitQuatProduct(R, quat1);
	quat1 = UnitQuatProduct(tmp, Conjugate(R));
	mView = quat1.v;
}

void CCamera::RotateX(float angle)
{
	Vector3f tmp = CrossProduct3f(mUp, mView);
	Rotate(tmp.x, tmp.y, tmp.z, angle);
}

void CCamera::RotateY(float angle)
{
	RotateViewVec(mUp.x, mUp.y, mUp.z, angle);
}

void CCamera::RotateZ(float angle)
{
	RotateUpVec(mView.x, mView.y, mView.z, angle);	
}

void CCamera::MoveForward(float dist)
{
	mPosition.x += (mView.x * dist);
	mPosition.y += (mView.y * dist);
	mPosition.z += (mView.z * dist);
}

void CCamera::MoveLeft(float dist)
{
	Vector3f tmp = CrossProduct3f(mUp, mView);
	mPosition.x += tmp.x * dist;
	mPosition.y += tmp.y * dist;
	mPosition.z += tmp.z * dist;
}

void CCamera::GetModelview(Matrix4f &mat)
{
	mat.LoadIdentity();
	mUp.Normalize();
	mat.LookAt(mPosition, mPosition+mView, mUp);
}

void CCamera::GetProjection(Matrix4f &mat)
{
	mat.LoadIdentity();
	mat.Perspective(mFOV, mAspect, mZNear, mZFar);
}

void CCamera::GetModelviewProjection(Matrix4f &mat)
{
	mat.LoadIdentity();
	mat.Perspective(mFOV, mAspect, mZNear, mZFar);
	mUp.Normalize();
	mat.LookAt(mPosition, mPosition+mView, mUp);
}

void CCamera::Render()
{
	Matrix4f mv, proj;
	GetModelview(mv);
	GetProjection(proj);
	Renderer->SetCamera(mv, proj);

	CSceneNode::Render();
}

Vector2f CCamera::IntersectFloor(float mx, float my)
{ 
	float s = mZNear / (mAspect * tanf(Deg2Rad(mFOV)));
	Vector3f right = CrossProduct3f(mView, mUp);
	Vector3f view = mView * mZNear + my*s*mUp + mx*s*right;
	float c = mPosition.z / view.z;
	return Vector2f(mPosition.x - view.x * c, mPosition.y - view.y * c);
}

