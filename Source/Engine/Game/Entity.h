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

	bool HasComponent(ComponentType type) const;
	void AddComponent(Component *comp);

	template<class CType>
	CType* GetComponent(ComponentType type) const
	{
		auto itr = _components.find(type);
		return (itr != _components.end()) ? static_cast<CType*>(itr->second.get()) : nullptr;
	}

	EntityId GetId() const;
};