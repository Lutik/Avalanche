#include "stdafx.h"

#include "CameraComponent.h"

Matrix4f CameraComponent::GetViewMatrix(TransformComponent *transform) const
{
	Vector3f up = RotateVector({0,0,1}, transform->rotation);
	Vector3f view = RotateVector({1,0,0}, transform->rotation);

	up.Normalize();
	return Matrix4f::LookAt(transform->position, transform->position + view, up);
}


PerspectiveCameraComponent::PerspectiveCameraComponent(float fov_, float aspect_, float znear_, float zfar_)
	: fov(fov_)
	, zNear(znear_)
	, zFar(zfar_)
	, aspect(aspect_)
{
}

Matrix4f PerspectiveCameraComponent::GetProjectionMatrix() const
{
	return Matrix4f::Perspective(fov, aspect, zNear, zFar);
}