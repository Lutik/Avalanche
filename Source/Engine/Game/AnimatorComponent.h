#pragma once

#include "Component.h"

struct TransformComponent;

struct AnimatorComponent : public Component
{
	virtual void Update(TransformComponent *transform, float dt) = 0;

	virtual ComponentType getType() const override { return ComponentType::ANIMATOR; }
};

class AnimatorContainerComponent : public AnimatorComponent
{
	std::vector<std::unique_ptr<AnimatorComponent>> _anims;
public:
	void AddComponent(AnimatorComponent *anim)
	{
		_anims.push_back(std::unique_ptr<AnimatorComponent>(anim));
	}

	void Update(TransformComponent *transform, float dt) override
	{
		for(auto &anim : _anims)
		{
			anim->Update(transform, dt);
		}
	}
};