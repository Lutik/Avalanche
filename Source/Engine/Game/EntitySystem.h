#pragma once

#include "Entity.h"

class EntitySystem
{
	EntityId _last_entity_id = 0;

	typedef std::unique_ptr<Entity> EntityPtr;
	typedef std::vector<EntityPtr> EntityVector;
	EntityVector _entities;
public:

	Entity* CreateEntity();
	void DeleteEntity(EntityId id);
	Entity* GetEntity(EntityId id);

	void GetEntitiesWithComponentTypes(const std::vector<ComponentType> &compTypes, std::vector<Entity*> &entities);

	void Clear();
};