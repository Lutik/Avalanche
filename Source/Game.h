#pragma once

#include "GameApp.h"
#include "Font.h"
#include "Shader.h"

class TestLayer : public IGameLayer
{
	Matrix4f _modelview;
	Matrix4f _projection;

	Font font;
	ShaderProgram shader;
	Mesh mesh;

	void SetupMatrices();
	void SetupGL();

	Matrix4f GetMVPMatrix() const;

public:
	TestLayer();
	~TestLayer();

	virtual void onRender() override;
	virtual void onUpdate(float dt) override;
	virtual void onKeyDown(int key) override;
	//virtual void onMouseDown(int key) override;
	//virtual void onMouseUp(int key) override;
};