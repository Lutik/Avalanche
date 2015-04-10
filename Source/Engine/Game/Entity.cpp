#include "stdafx.h"

#include "Entity.h"

Entity::Entity(EntityId id)
	: _id(id)
{
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

EntityId Entity::GetId() const
{
	return _id;
}