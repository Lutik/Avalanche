#pragma once

#include "Component.h"

#include "Matrix.h"
#include "TransformComponent.h"

struct CameraComponent : public Component
{
	ComponentType getType() const override { return ComponentType::CAMERA; }

	virtual Matrix4f GetViewMatrix(TransformComponent *transform) const;
	virtual Matrix4f GetProjectionMatrix() const = 0;
};

struct PerspectiveCameraComponent : public CameraComponent
{
	float fov;
	float zNear, zFar;
	float aspect;

	PerspectiveCameraComponent(float fov, float aspect, float znear, float zfar);

	virtual Matrix4f GetProjectionMatrix() const override;
};