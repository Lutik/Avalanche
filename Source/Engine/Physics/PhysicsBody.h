#pragma once

#include <btBulletDynamicsCommon.h>

#include "Component.h"
#include "MotionState.h"
#include "TransformComponent.h"

std::unique_ptr<btCollisionShape> CubeShape(float size);
std::unique_ptr<btCollisionShape> BoxShape(float size_x, float size_y, float size_z);
std::unique_ptr<btCollisionShape> PlaneShape(Vector3f normal, float constant);

struct PhysicsBody : public Component
{
protected:
	std::unique_ptr<btCollisionShape> collisionShape;	
	AvMotionState motionState;

public:
	std::unique_ptr<btRigidBody> rigidBody;

	ComponentType getType() const override { return ComponentType::PHYSICS_BODY; }

	PhysicsBody(TransformComponent *transform, std::unique_ptr<btCollisionShape> collisionShape, float mass);
};