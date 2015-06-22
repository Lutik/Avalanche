#pragma once

#include <btBulletDynamicsCommon.h>

#include "TransformComponent.h"

class AvMotionState : public btMotionState
{
protected:
	TransformComponent *_transform = nullptr;
public:
	AvMotionState(TransformComponent *transform);

	void SetTransform(TransformComponent *transform);

	void getWorldTransform(btTransform &worldTrans) const override;
	void setWorldTransform(const btTransform &worldTrans) override;
};