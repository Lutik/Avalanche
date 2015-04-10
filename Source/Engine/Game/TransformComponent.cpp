#include "stdafx.h"

#include "TransformComponent.h"

Matrix4f TransformComponent::GetModelMatrix() const
{
	return Matrix4f::Translate(position) * RotationMatrix(rotation) * Matrix4f::Scale({scale, scale, scale});
}

void TransformComponent::Rotate(Vector3f v, float angle)
{
	Quaternion rq = RotationToQuaternion(v, angle);
	rotation = UnitQuatProduct(rotation, rq);
}