#pragma once

#include "Component.h"

typedef std::uint16_t EntityId;

class Entity
{
	EntityId _id;
	std::map<ComponentType, std::unique_ptr<Component>> _components;
public:
	Entity(EntityId id);

	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	Component *GetComponent(ComponentType type) const;
	void AddComponent(Component *comp);

	EntityId GetId() const;
};