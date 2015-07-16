#pragma once

#include "Scene.h"
#include "Renderer.h"

#include "EntityContainer.h"
#include "AnimatorSystem.h"
#include "PhysicsSystem.h"

#include "FpsCounter.h"

class TestScene : public Scene
{
	Renderer _render;
	AnimatorSystem _animator;
	PhysicsSystem _physics;

	EntityContainer entities;

	Mesh::Ptr _cubeMesh;

	FpsCounter _fps;

	Entity* CreateCube(Vector3f pos);
	Entity* CreateCamera(Vector3f pos, Vector3f view);
	Entity* CreatePlane();
	Entity* CreateLight(Vector3f pos, Vector3f color);
public:
	TestScene();
	~TestScene();

	virtual void onUpdate(float dt) override;
};