#ifndef AvalancheCameraH
#define AvalancheCameraH

#include "math3d.h"

class Camera 
{
public:
	//initialization
	void SetPerspective(float fov, float aspect, float zNear, float zFar);
	void SetPosition(Vector3f pos);
	void SetUpVector(Vector3f up);
	void SetViewVector(Vector3f view);
	//rotations
	void RotateViewVec(float x, float y, float z, float angle);
	void RotateUpVec(float x, float y, float z, float angle);
	void Rotate(float x, float y, float z, float angle);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	//movements
	void MoveForward(float dist);
	void MoveBackward(float dist) { MoveForward(-dist); }
	void MoveLeft(float dist);
	void MoveRight(float dist) { MoveLeft(-dist); }
	//get camera info
	Vector3f GetView() const { return _view; }
	Vector3f GetPos() const { return _pos; }
	Vector3f GetUp() const { return _up; }
	float GetZFar() const { return mZFar; }
	//apply camera to OpenGL
	Matrix4f GetViewMatrix();
	Matrix4f GetProjectionMatrix();
	Matrix4f GetViewProjectionMatrix();
private:
	//position and orientation
	Vector3f _pos;
	Vector3f _view;
	Vector3f _up;
	//perspective
	float mFOV;
	float mAspect;
	float mZNear, mZFar;
	//  
};

#endif
