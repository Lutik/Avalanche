#include "stdafx.h"
#include "MotionState.h"

inline btVector3 toBtVec(const Vector3f &vec)
{
	return btVector3(vec.x, vec.y, vec.z);
}

inline btQuaternion toBtQuat(const Quaternion &quat)
{
	return btQuaternion(quat.x, quat.y, quat.z, quat.w);
}

inline Vector3f toAvVec(const btVector3 &vec)
{
	return Vector3f(vec.getX(), vec.getY(), vec.getZ());
}

inline Quaternion toAvQuat(const btQuaternion &quat)
{
	return Quaternion(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
}

AvMotionState::AvMotionState(TransformComponent *transform)
	: _transform(transform)
{
}

void AvMotionState::SetTransform(TransformComponent *transform)
{
	_transform = transform;
}

void AvMotionState::getWorldTransform(btTransform &worldTrans) const
{
	worldTrans.setOrigin( toBtVec(_transform->position) );
	worldTrans.setRotation( toBtQuat(_transform->rotation) );
}

void AvMotionState::setWorldTransform(const btTransform &worldTrans)
{
	_transform->position = toAvVec(worldTrans.getOrigin());
	_transform->rotation = toAvQuat(worldTrans.getRotation());
}
