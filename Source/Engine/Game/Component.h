#pragma once

enum class ComponentType
{
	NONE,
	TRANSFORM, // положение в пространстве
};

struct Component
{
	virtual ComponentType getType() const = 0;
};