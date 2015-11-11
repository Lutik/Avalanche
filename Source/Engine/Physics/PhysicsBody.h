#pragma once

#include <btBulletDynamicsCommon.h>

#include "Component.h"
#include "MotionState.h"
#include "TransformComponent.h"
#include "PhysicsShapes.h"

struct PhysicsBody : public Component
{
protected:
	CollisionModelPtr collisionModel;	
	AvMotionState motionState;

public:
	std::unique_ptr<btRigidBody> rigidBody;

	ComponentType getType() const override { return ComponentType::PHYSICS_BODY; }

	PhysicsBody(TransformComponent *transform, CollisionModelPtr collisionModel, float mass);
};