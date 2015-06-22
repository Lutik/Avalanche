#pragma once

#include <btBulletDynamicsCommon.h>

#include "EntityContainer.h"
#include "System.h"
#include "TransformComponent.h"
#include "PhysicsBody.h"

class PhysicsSystem : public GameSystem
{
	std::unique_ptr<btBroadphaseInterface> _broadphase;
	std::unique_ptr<btCollisionConfiguration> _collisionConfig;
	std::unique_ptr<btCollisionDispatcher> _dispatcher;
	std::unique_ptr<btSequentialImpulseConstraintSolver> _solver;

	std::unique_ptr<btDiscreteDynamicsWorld> _world;

	struct Body {
		Entity *entity;
		TransformComponent *trans;
		PhysicsBody *body;
	};
	std::vector<Body> _bodies;

public:
	void Init(EntityContainer *entities) override;

	void Update(float dt) override;

	void OnAddComponent(Entity *entity, ComponentType compType) override;
	void OnRemoveComponent(Entity *entity, ComponentType compType) override;
};