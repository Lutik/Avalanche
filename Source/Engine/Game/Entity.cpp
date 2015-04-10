#include "stdafx.h"

#include "Entity.h"

Entity::Entity(EntityId id)
	: _id(id)
{
}

bool Entity::HasComponent(ComponentType type) const
{
	auto itr = _components.find(type);
	return (itr != _components.end());
}

void Entity::AddComponent(Component *comp)
{
	_components.emplace(comp->getType(), std::unique_ptr<Component>(comp));
}

EntityId Entity::GetId() const
{
	return _id;
}