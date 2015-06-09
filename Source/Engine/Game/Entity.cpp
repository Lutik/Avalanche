#include "stdafx.h"

#include "Entity.h"

bool Entity::HasComponent(ComponentType type) const
{
	auto itr = _components.find(type);
	return (itr != _components.end());
}

Component* Entity::GetComponent(ComponentType type) const
{
	auto itr = _components.find(type);
	return (itr != _components.end()) ? itr->second.get() : nullptr;
}

void Entity::AddComponent(Component *comp)
{
	_components.emplace(comp->getType(), std::unique_ptr<Component>(comp));
}

void Entity::RemoveComponent(ComponentType compType)
{
	_components.erase(compType);
}