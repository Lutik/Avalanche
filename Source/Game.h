#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Model.h"
#include "Renderer.h"

class TestScene : public Scene
{
	Camera _camera;
	Model *_model;
	float meshAngle = 0.0f;
	Renderer _render;
public:
	TestScene();

	virtual void onRender() override;
	virtual void onUpdate(float dt) override;
};