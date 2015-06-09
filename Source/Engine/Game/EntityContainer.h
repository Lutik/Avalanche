#pragma once

#include "Entity.h"

class GameSystem;

class EntityContainer
{
	typedef std::unique_ptr<Entity> EntityPtr;
	typedef std::vector<EntityPtr> EntityVector;
	EntityVector _entities;

	std::map<ComponentType, std::vector<GameSystem*>> _listeners;
public:

	Entity* CreateEntity();
	void DeleteEntity(Entity *entity);

	void AddComponent(Entity *entity, Component *component);
	void RemoveComponent(Entity *entity, ComponentType compType);

	void AddListener(ComponentType compType, GameSystem *system);
	void RemoveListener(ComponentType compType, GameSystem *system);

	template<class CType>
	CType* GetComponent(Entity *entity, ComponentType type) const
	{
		return static_cast<CType*>(entity->GetComponent(type));
	}

	bool HasComponents(const Entity *entity, const ComponentTypeSet &compTypes) const;

	std::vector<Entity*> GetEntitiesWithComponentTypes(const ComponentTypeSet &compTypes) const;
};