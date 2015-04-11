#pragma once

#include "Component.h"

struct TransformComponent;

struct AnimatorComponent : public Component
{
	float speed;

	virtual void Update(TransformComponent *transform, float dt) = 0;

	virtual ComponentType getType() const override { return ComponentType::ANIMATOR; }
};