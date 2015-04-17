#pragma once

#include "Scene.h"
#include "Renderer.h"

#include "EntityContainer.h"
#include "AnimatorSystem.h"
#include "TransformComponent.h"


class TestScene : public Scene
{
	Renderer _render;
	AnimatorSystem _animator;

	EntityContainer entities;

	Entity* CreateCube(Vector3f pos, float scale);
	Entity* CreateCamera(Vector3f pos, Vector3f view);
	Entity* CreatePlane();
	Entity* CreateLight(Vector3f pos, Vector3f color);
public:
	TestScene();

	virtual void onUpdate(float dt) override;
};