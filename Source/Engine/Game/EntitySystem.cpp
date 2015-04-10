#include "stdafx.h"

#include "EntitySystem.h"

Entity* EntitySystem::CreateEntity()
{
	_entities.push_back(std::make_unique<Entity>(_last_entity_id++));
	return _entities.back().get();
}

void EntitySystem::DeleteEntity(EntityId id)
{
	auto itr = std::find_if(_entities.begin(), _entities.end(), [=](const EntityPtr& entity){
		return entity->GetId() == id;
	});
	if( itr != _entities.end() ) {
		_entities.erase(itr);
	}
}

Entity* EntitySystem::GetEntity(EntityId id)
{
	auto itr = std::find_if(_entities.begin(), _entities.end(), [=](const EntityPtr& entity){
		return entity->GetId() == id;
	});
	return (itr != _entities.end()) ? itr->get() : nullptr;
}

void EntitySystem::GetEntitiesWithComponentTypes(const std::vector<ComponentType> &compTypes, std::vector<Entity*> &entities)
{
	for(EntityPtr &entity : _entities)
	{
		bool hasComponents = true;
		for(ComponentType cType : compTypes) {
			if( entity->GetComponent(cType) == nullptr ) {
				hasComponents = false;
				break;
			}
		}

		if( hasComponents ) {
			entities.push_back(entity.get());
		}
	}
}

void EntitySystem::Clear()
{
	_entities.clear();
	_last_entity_id = 0;
}