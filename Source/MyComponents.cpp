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

	if( Av::input->KeyPressed(SDL_SCANCODE_RIGHT) ) {
		transform->position += right * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_LEFT) ) {
		transform->position -= right * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_UP) ) {
		transform->position += forward * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_DOWN) ) {
		transform->position -= forward * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_A) ) {
		transform->position += up * (speed * dt);
	}
	if( Av::input->KeyPressed(SDL_SCANCODE_Z) ) {
		transform->position -= up * (speed * dt);
	}
}