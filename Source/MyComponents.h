#pragma once

#include "AnimatorComponent.h"


struct MyAnimComponent : public AnimatorComponent
{
	void Update(TransformComponent *transform, float dt) override;
};

struct MyInputComponent : public AnimatorComponent
{
	float speed = 1.0f;

	MyInputComponent(float sp) : speed(sp) {}

	void Update(TransformComponent *transform, float dt) override;
};

struct CamControlComponent : public AnimatorComponent
{
	void Update(TransformComponent *transform, float dt) override;
};