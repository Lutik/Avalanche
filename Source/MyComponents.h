#pragma once

#include "AnimatorComponent.h"


class MyAnimComponent : public AnimatorComponent
{
	void Update(TransformComponent *transform, float dt) override;
};

class MyInputComponent : public AnimatorComponent
{
	void Update(TransformComponent *transform, float dt) override;
};