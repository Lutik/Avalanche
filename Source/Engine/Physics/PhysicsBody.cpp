#include "stdafx.h"

#include "PhysicsBody.h"

std::unique_ptr<btCollisionShape> CubeShape(float size)
{
	size *= 0.5f;
	return std::make_unique<btBoxShape>(btVector3(size, size, size));
}

std::unique_ptr<btCollisionShape> BoxShape(float size_x, float size_y, float size_z)
{
	btVector3 boxSize(size_x * 0.5f, size_y * 0.5f, size_z * 0.5f);
	return std::make_unique<btBoxShape>(boxSize);
}

std::unique_ptr<btCollisionShape> PlaneShape(Vector3f n, float constant)
{
	return std::make_unique<btStaticPlaneShape>(btVector3(n.x, n.y, n.z), constant);
}

PhysicsBody::PhysicsBody(TransformComponent *transform, std::unique_ptr<btCollisionShape> colShape, float mass)
	: motionState(transform)
	, collisionShape( std::move(colShape) )
{
	btVector3 localInertia(0, 0, 0);
	collisionShape->calculateLocalInertia(mass, localInertia);
	btRigidBody::btRigidBodyConstructionInfo info(mass, &motionState, collisionShape.get(), localInertia);
	rigidBody = std::make_unique<btRigidBody>(info);
}