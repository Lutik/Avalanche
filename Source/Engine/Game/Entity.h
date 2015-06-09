#pragma once

#include "Component.h"

class Entity
{
	std::map<ComponentType, std::unique_ptr<Component>> _components;
public:
	Entity() = default;

	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	bool HasComponent(ComponentType type) const;
	void AddComponent(Component *comp);
	void RemoveComponent(ComponentType type);
	Component *GetComponent(ComponentType type) const;
};