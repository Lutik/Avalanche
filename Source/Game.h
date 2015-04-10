#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Model.h"
#include "Renderer.h"

#include "EntitySystem.h"

#include "TransformComponent.h"


class TestScene : public Scene
{
	Camera _camera;

	Renderer _render;

	EntityContainer entities;

	void MoveCubes(float dt);

	void CreateCube(Vector3f pos, float scale);
public:
	TestScene();

	virtual void onRender() override;
	virtual void onUpdate(float dt) override;
};