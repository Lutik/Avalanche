#pragma once

#include "Component.h"
#include "Vector3.h"

struct PointLightComponent : public Component
{
	Vector3f color;
	Vector3f attenuation;

	ComponentType getType() const override { return ComponentType::POINT_LIGHT; }

	PointLightComponent(Vector3f col, Vector3f att) : color(col), attenuation(att) {}
};