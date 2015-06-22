#include "stdafx.h"

#include "PhysicsSystem.h"


void PhysicsSystem::Init(EntityContainer *entities)
{
	GameSystem::Init(entities);

	_entities->AddListener(ComponentType::TRANSFORM, this);
	_entities->AddListener(ComponentType::PHYSICS_BODY, this);

	_broadphase = std::make_unique<btDbvtBroadphase>();
	_collisionConfig = std::make_unique<btDefaultCollisionConfiguration>();
	_dispatcher = std::make_unique<btCollisionDispatcher>(_collisionConfig.get());
	_solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	_world = std::make_unique<btDiscreteDynamicsWorld>(_dispatcher.get(), _broadphase.get(), _solver.get(), _collisionConfig.get());

	_world->setGravity(btVector3(0.0f, 0.0f, -9.8f));

	// add static plane


	//
	_bodies.clear();
	auto objects = _entities->GetEntitiesWithComponentTypes({ComponentType::TRANSFORM, ComponentType::PHYSICS_BODY});
	for(Entity *entity : objects)
	{
		TransformComponent *ctransform = _entities->GetComponent<TransformComponent>(entity, ComponentType::TRANSFORM);
		PhysicsBody *cbody = _entities->GetComponent<PhysicsBody>(entity, ComponentType::PHYSICS_BODY);
		_bodies.push_back( {entity, ctransform, cbody} );
		_world->addRigidBody(cbody->rigidBody.get());
	}
}

void PhysicsSystem::Update(float dt)
{
	_world->stepSimulation(dt, 4);

	// todo: limit fall somehow
}

void PhysicsSystem::OnAddComponent(Entity *entity, ComponentType compType)
{
	const ComponentTypeSet physicsComps = {ComponentType::TRANSFORM, ComponentType::PHYSICS_BODY};
	if(_entities->HasComponents(entity, physicsComps))
	{
		TransformComponent *ctransform = _entities->GetComponent<TransformComponent>(entity, ComponentType::TRANSFORM);
		PhysicsBody *cbody = _entities->GetComponent<PhysicsBody>(entity, ComponentType::PHYSICS_BODY);
		_bodies.push_back( {entity, ctransform, cbody} );
		_world->addRigidBody(cbody->rigidBody.get());
	}
}

void PhysicsSystem::OnRemoveComponent(Entity *entity, ComponentType compType)
{
	if( compType == ComponentType::TRANSFORM || compType == ComponentType::PHYSICS_BODY)
	{
		auto itr = std::find_if(_bodies.begin(), _bodies.end(), [=](const Body &body){
			return body.entity == entity;
		});
		if( itr != _bodies.end() ) {
			_world->removeRigidBody(itr->body->rigidBody.get());
			_bodies.erase(itr);
		}
	}
}