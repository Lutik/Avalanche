#pragma once

#include "EntityContainer.h"

class GameSystem
{
protected:
	EntityContainer *_entities = nullptr;
public:
	virtual void Init(EntityContainer *entities);

	virtual void Update(float dt) = 0;

	virtual void OnAddComponent(Entity *entity, ComponentType compType) {}
	virtual void OnRemoveComponent(Entity *entity, ComponentType compType) {}
};