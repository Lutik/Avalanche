#include "stdafx.h"
#include "Game.h"
#include "ImageLoaders.h"
#include "ModelLoaders.h"
#include "Utils.h"
#include "ResourceManager.h"

void TestScene::SetupGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisable(GL_CULL_FACE);
}

TestScene::TestScene()
{
	SetupGL();

	meshPos = Vector3f(0.0f, 0.0f, -6.0f);

	_model = Av::resourceManager.GetModel("MetalCube");

	_camera.SetPosition({0.0f, -6.0f, 3.0f});
	_camera.SetViewVector({0.0f, 1.0f, -0.5f});
	_camera.SetUpVector({0.0f, 0.0f, 1.0f});
	_camera.SetPerspective(45.0f, application->GetAspectRatio(), 0.2f, 30.0f);
}

void TestScene::onUpdate(float dt)
{
	meshAngle += 45.0f * dt;
	if( meshAngle >= 360.0f )
		meshAngle -= 360.0f;
}

void TestScene::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Matrix4f modelMatrix = Matrix4f::Scale({0.06f, 0.06f, 0.06f});
	modelMatrix *= Matrix4f::Rotate(meshAngle, {0.0f, 0.0f, 1.0f});

	Vector3f light_dir(1.0f, 1.0f, -5.0f);
	light_dir.Normalize();

	_model->Bind();

	ShaderProgram *shader = _model->_material->GetShader();
	shader->SetUniform("light_dir", light_dir);
	shader->SetUniform("modelview", _camera.GetViewMatrix() * modelMatrix);
	shader->SetUniform("projection", _camera.GetProjectionMatrix());

	_model->Draw();
}

void TestScene::onKeyDown(int key)
{
	if(key == SDL_SCANCODE_ESCAPE)
		application->Shutdown();
}

TestScene::~TestScene()
{
}