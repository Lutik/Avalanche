#include "stdafx.h"

#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(TransformComponent *transform, CollisionModelPtr colModel, float mass)
	: motionState(transform)
	, collisionModel(std::move(colModel))
{
	btVector3 localInertia(0, 0, 0);
	collisionModel->getShape()->calculateLocalInertia(mass, localInertia);
	btRigidBody::btRigidBodyConstructionInfo info(mass, &motionState, collisionModel->getShape(), localInertia);
	rigidBody = std::make_unique<btRigidBody>(info);
}