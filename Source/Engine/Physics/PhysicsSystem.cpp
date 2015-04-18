#include "stdafx.h"

#include "PhysicsSystem.h"


void PhysicsSystem::Init()
{
	_broadphase = std::make_unique<btDbvtBroadphase>();
	_collisionConfig = std::make_unique<btDefaultCollisionConfiguration>();
	_dispatcher = std::make_unique<btCollisionDispatcher>(_collisionConfig.get());
	_solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	_world = std::make_unique<btDiscreteDynamicsWorld>(_dispatcher.get(), _broadphase.get(), _solver.get(), _collisionConfig.get());

	_world->setGravity(btVector3(0.0f, 0.0f, -9.8f));
}

void PhysicsSystem::Update(EntityContainer &entities, float dt)
{
	_world->stepSimulation(dt, 4);
}