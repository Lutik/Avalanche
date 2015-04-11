#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"

#include "EntityContainer.h"
#include "AnimatorSystem.h"
#include "TransformComponent.h"


class TestScene : public Scene
{
	Camera _camera;

	Renderer _render;
	AnimatorSystem _animator;

	EntityContainer entities;

	Entity* CreateCube(Vector3f pos, float scale);
public:
	TestScene();

	virtual void onRender() override;
	virtual void onUpdate(float dt) override;
};