#pragma once

#include "Component.h"

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"

struct TransformComponent : public Component
{
	Quaternion rotation;
	Vector3f position;
	float scale = 1.0f;

	Matrix4f GetModelMatrix() const;

	void Rotate(Vector3f v, float angle);

	ComponentType getType() const override { return ComponentType::TRANSFORM; }
};