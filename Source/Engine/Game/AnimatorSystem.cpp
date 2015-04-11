#include "stdafx.h"

#include "AnimatorSystem.h"

#include "TransformComponent.h"
#include "AnimatorComponent.h"

void AnimatorSystem::Update(EntityContainer &entities, float dt)
{
	auto objects = entities.GetEntitiesWithComponentTypes({ComponentType::ANIMATOR, ComponentType::TRANSFORM});
	for(Entity *entity : objects)
	{
		TransformComponent *ctransform = entity->GetComponent<TransformComponent>(ComponentType::TRANSFORM);
		AnimatorComponent *canim = entity->GetComponent<AnimatorComponent>(ComponentType::ANIMATOR);

		canim->Update(ctransform, dt);
	}
}