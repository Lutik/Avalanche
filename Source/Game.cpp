#include "stdafx.h"
#include "Game.h"
#include "ImageLoaders.h"
#include "ModelLoaders.h"
#include "Utils.h"

GLuint vao;

void TestLayer::SetupGL()
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

TestLayer::TestLayer()
{
	SetupGL();

	mesh = LoadMeshOBJ("Resources/cube.obj");
	meshPos = Vector3f(0.0f, 0.0f, -6.0f);

	Image2D img = loadTexture("Resources/metal.png");
	texture.SetImage(img);

	_camera.SetPosition({0.0f, -6.0f, 3.0f});
	_camera.SetViewVector({0.0f, 1.0f, -0.5f});
	_camera.SetUpVector({0.0f, 0.0f, 1.0f});
	_camera.SetPerspective(45.0f, application->GetAspectRatio(), 0.2f, 30.0f);

	shader.Link("Resources/Shaders/Simple.vsh", "Resources/Shaders/Simple.fsh");
}

void TestLayer::onUpdate(float dt)
{
	meshAngle += 45.0f * dt;
	if( meshAngle >= 360.0f )
		meshAngle -= 360.0f;
}

void TestLayer::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);

	Matrix4f modelMatrix = Matrix4f::Scale({0.06f, 0.06f, 0.06f});
	modelMatrix *= Matrix4f::Rotate(meshAngle, {0.0f, 0.0f, 1.0f});

	texture.Bind(0);

	Vector3f light_dir(1.0f, 1.0f, -5.0f);
	light_dir.Normalize();
	shader.Bind();
	shader.SetUniform("texture", 0);
	shader.SetUniform("light_dir", light_dir);
	shader.SetUniform("modelview", _camera.GetViewMatrix() * modelMatrix);
	shader.SetUniform("projection", _camera.GetProjectionMatrix());

	mesh->Draw();
}

void TestLayer::onKeyDown(int key)
{
	if(key == SDL_SCANCODE_ESCAPE)
		application->Shutdown();
}

TestLayer::~TestLayer()
{
}