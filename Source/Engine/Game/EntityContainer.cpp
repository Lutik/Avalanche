#include "stdafx.h"

#include "EntityContainer.h"
#include "System.h"

Entity* EntityContainer::CreateEntity()
{
	_entities.push_back(std::make_unique<Entity>());
	return _entities.back().get();
}

void EntityContainer::DeleteEntity(Entity* entity)
{
	auto itr = std::find_if(_entities.begin(), _entities.end(), [=](const EntityPtr& ent){
		return ent.get() == entity;
	});
	if( itr != _entities.end() ) {

		// notify listeners
		for(auto &pair : _listeners)
		{
			if(entity->HasComponent(pair.first)) {
				for(GameSystem *system : pair.second) {
					system->OnRemoveComponent(entity, pair.first);
				}
			}
		}

		_entities.erase(itr);
	}
}

void EntityContainer::AddComponent(Entity *entity, Component *component)
{
	entity->AddComponent(component);

	auto &listeners = _listeners[component->getType()];
	for(GameSystem *system : listeners) {
		system->OnAddComponent(entity,component->getType());
	}
}

void EntityContainer::RemoveComponent(Entity *entity, ComponentType compType)
{
	entity->RemoveComponent(compType);

	auto &listeners = _listeners[compType];
	for(GameSystem *system : listeners) {
		system->OnRemoveComponent(entity, compType);
	}
}

bool EntityContainer::HasComponents(const Entity *entity, const ComponentTypeSet &compTypes) const
{
	bool hasComponents = true;
	for(ComponentType cType : compTypes) {
		if( !entity->HasComponent(cType)  ) {
			hasComponents = false;
			break;
		}
	}
	return hasComponents;
}

std::vector<Entity*> EntityContainer::GetEntitiesWithComponentTypes(const ComponentTypeSet &compTypes) const
{
	std::vector<Entity*> result;
	for(const EntityPtr &entity : _entities)
	{
		if( HasComponents(entity.get(), compTypes) ) {
			result.push_back(entity.get());
		}
	}
	return result;
}

void EntityContainer::AddListener(ComponentType compType, GameSystem *system)
{
	auto &vec = _listeners[compType];
	auto itr = std::find(vec.begin(), vec.end(), system);
	if( itr == vec.end() ) {
		vec.push_back(system);
	}
}

void EntityContainer::RemoveListener(ComponentType compType, GameSystem *system)
{
	auto itr = _listeners.find(compType);
	if( itr != _listeners.end() && !itr->second.empty()){
		auto itr2 = std::find(itr->second.begin(), itr->second.end(), system);
		if( itr2 != itr->second.end() )
			itr->second.erase(itr2);
	}
}