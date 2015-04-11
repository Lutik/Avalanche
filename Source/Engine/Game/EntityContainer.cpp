#include "stdafx.h"

#include "EntityContainer.h"

Entity* EntityContainer::CreateEntity()
{
	_entities.push_back(std::make_unique<Entity>(_last_entity_id++));
	return _entities.back().get();
}

void EntityContainer::DeleteEntity(EntityId id)
{
	auto itr = std::find_if(_entities.begin(), _entities.end(), [=](const EntityPtr& entity){
		return entity->GetId() == id;
	});
	if( itr != _entities.end() ) {
		_entities.erase(itr);
	}
}

Entity* EntityContainer::GetEntity(EntityId id)
{
	auto itr = std::find_if(_entities.begin(), _entities.end(), [=](const EntityPtr& entity){
		return entity->GetId() == id;
	});
	return (itr != _entities.end()) ? itr->get() : nullptr;
}

std::vector<Entity*> EntityContainer::GetEntitiesWithComponentTypes(const std::vector<ComponentType> &compTypes) const
{
	std::vector<Entity*> result;
	for(const EntityPtr &entity : _entities)
	{
		bool hasComponents = true;
		for(ComponentType cType : compTypes) {
			if( !entity->HasComponent(cType)  ) {
				hasComponents = false;
				break;
			}
		}

		if( hasComponents ) {
			result.push_back(entity.get());
		}
	}
	return result;
}

void EntityContainer::Clear()
{
	_entities.clear();
	_last_entity_id = 0;
}