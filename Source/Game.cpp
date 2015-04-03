#include "stdafx.h"
#include "Game.h"
#include "ImageLoaders.h"
#include "ModelLoaders.h"
#include "Utils.h"
#include "ResourceManager.h"

GLuint vao;

void TestScene::SetupGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisable(GL_CULL_FACE);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

TestScene::TestScene()
{
	SetupGL();

	mesh = Av::resourceManager.GetMesh("Cube");
	meshPos = Vector3f(0.0f, 0.0f, -6.0f);

	material = Av::resourceManager.GetMaterial("Metal");

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

	glBindVertexArray(vao);

	Matrix4f modelMatrix = Matrix4f::Scale({0.06f, 0.06f, 0.06f});
	modelMatrix *= Matrix4f::Rotate(meshAngle, {0.0f, 0.0f, 1.0f});

	material->Bind();

	Vector3f light_dir(1.0f, 1.0f, -5.0f);
	light_dir.Normalize();

	ShaderProgram *shader = material->GetShader();
	shader->SetUniform("light_dir", light_dir);
	shader->SetUniform("modelview", _camera.GetViewMatrix() * modelMatrix);
	shader->SetUniform("projection", _camera.GetProjectionMatrix());

	mesh->Draw();
}

void TestScene::onKeyDown(int key)
{
	if(key == SDL_SCANCODE_ESCAPE)
		application->Shutdown();
}

TestScene::~TestScene()
{
}