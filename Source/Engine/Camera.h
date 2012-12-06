#ifndef AvalancheCameraH
#define AvalancheCameraH

#include "math3d.h"
#include "Scene.h"

class CCamera : public CSceneNode 
{
public:
	CCamera();
	~CCamera();
	//initialization
	void SetPerspective(float fov, float aspect, float zNear, float zFar);
	void SetUpVector(float x, float y, float z);
	void SetViewVector(float x, float y, float z);
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
	Vector3f GetView() { return mView; }
	Vector3f GetPos() { return mPosition; }
	Vector3f GetUp() { return mUp; }
	float GetZFar() { return mZFar; }
	//apply camera to OpenGL
	void GetModelview(Matrix4f &mat);
	void GetProjection(Matrix4f &mat);
	void GetModelviewProjection(Matrix4f &mat);

	void Render();

	//Misc
	Vector2f IntersectFloor(float mx, float my);
private:
	//position and orientation
	Vector3f mView;
	Vector3f mUp;
	//float mDist; //useful only for 3rd person camera
	//perspective
	float mFOV;
	float mAspect;
	float mZNear, mZFar;
	//  
};

#endif
