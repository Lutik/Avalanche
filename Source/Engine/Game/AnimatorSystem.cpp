#include "stdafx.h"

#include "AnimatorSystem.h"

#include "TransformComponent.h"
#include "AnimatorComponent.h"

void AnimatorSystem::Update(float dt)
{
	auto objects = _entities->GetEntitiesWithComponentTypes({ComponentType::ANIMATOR, ComponentType::TRANSFORM});
	for(Entity *entity : objects)
	{
		TransformComponent *ctransform = _entities->GetComponent<TransformComponent>(entity, ComponentType::TRANSFORM);
		AnimatorComponent *canim = _entities->GetComponent<AnimatorComponent>(entity, ComponentType::ANIMATOR);

		canim->Update(ctransform, dt);
	}
}