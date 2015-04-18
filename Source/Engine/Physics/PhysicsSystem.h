#pragma once

#include <btBulletDynamicsCommon.h>

#include "EntityContainer.h"

class PhysicsSystem
{
	std::unique_ptr<btBroadphaseInterface> _broadphase;
	std::unique_ptr<btCollisionConfiguration> _collisionConfig;
	std::unique_ptr<btCollisionDispatcher> _dispatcher;
	std::unique_ptr<btSequentialImpulseConstraintSolver> _solver;

	std::unique_ptr<btDiscreteDynamicsWorld> _world;
public:
	void Init();

	void Update(EntityContainer &entities, float dt);
};