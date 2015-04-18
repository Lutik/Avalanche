#include "stdafx.h"

#include "MyComponents.h"
#include "TransformComponent.h"
#include "Input.h"


void MyAnimComponent::Update(TransformComponent *transform, float dt)
{
	transform->Rotate({0,0,1}, 45.0f * dt);
}

void MyInputComponent::Update(TransformComponent *transform, float dt)
{
	const Vector3f right = {1,0,0};
	const Vector3f forward = {0,1,0};
	const Vector3f up = {0,0,1};

	if( Av::input->KeyPressed(SDL_SCANCODE_D) ) {
		transform->position += right * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_A) ) {
		transform->position -= right * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_W) ) {
		transform->position += forward * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_S) ) {
		transform->position -= forward * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_Z) ) {
		transform->position += up * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_X) ) {
		transform->position -= up * (speed * dt);
	}
}

void CamControlComponent::Update(TransformComponent *transform, float dt)
{
	Vector3f view = RotateVector({1,0,0}, transform->rotation);
	view.Normalize();
	Vector3f up = {0,0,1};
	Vector3f side = Cross(view, up);

	const float MOVE_SPEED = 3.0f;
	const float ROTATION_SPEED = 0.7f;

	if( Av::input->KeyPressed(SDL_SCANCODE_UP) ) {
		transform->position += view * MOVE_SPEED * dt;
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_DOWN) ) {
		transform->position -= view * MOVE_SPEED * dt;
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_RIGHT) ) {
		transform->position += side * MOVE_SPEED * dt;
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_LEFT) ) {
		transform->position -= side * MOVE_SPEED * dt;
	}

	int mouse_dx = Av::input->GetMouseDX();
	int mouse_dy = Av::input->GetMouseDY();

	const int MOUSE_RIGHT = 3;
	bool mouseLook = Av::input->MousePressed(MOUSE_RIGHT);
	Av::input->GrabMouse(mouseLook);
	Av::input->ShowMouse(!mouseLook);

	// Rotation
	if( mouseLook )
	{
		// Find up vector (0,0,1) in local quaternion space
		Vector3f qup = RotateVector({0,0,1}, Conjugate(transform->rotation));
		// rotate horizontally
		Quaternion qhor = RotationToQuaternion(qup, -ROTATION_SPEED * mouse_dx);
		transform->rotation = UnitQuatProduct(transform->rotation, qhor);

		// rotate vertically
		Quaternion qver = RotationToQuaternion({0,1,0}, ROTATION_SPEED * mouse_dy);
		transform->rotation = UnitQuatProduct(transform->rotation, qver);

		transform->rotation.Normalize();
	}
}