#pragma once

#include "GameApp.h"
#include "Font.h"
#include "Shader.h"
#include "Camera.h"

class TestLayer : public IGameLayer
{
	Camera _camera;

	ShaderProgram shader;
	std::unique_ptr<Mesh> mesh;

	Vector3f meshPos;
	float meshAngle = 0.0f;

	void SetupGL();

public:
	TestLayer();
	~TestLayer();

	virtual void onRender() override;
	virtual void onUpdate(float dt) override;
	virtual void onKeyDown(int key) override;
	//virtual void onMouseDown(int key) override;
	//virtual void onMouseUp(int key) override;
};