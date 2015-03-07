#include "stdafx.h"
#include "Game.h"
#include "ImageLoaders.h"
#include "ModelLoaders.h"
#include "Utils.h"
#include <json/json.h>

GLuint vao;

void TestLayer::SetupGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDisable(GL_CULL_FACE);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

std::string GetStringFromJsonSettings()
{
	Json::Value root;
	Json::Reader reader;
	bool parseOK = reader.parse(ReadFile("resources/json_test.txt"), root, false);
	if( parseOK )
	{
		return root.get("text", "Default").asString();
	}
	else
	{
		return std::string("Error");
	}
}

TestLayer::TestLayer()
{
	SetupGL();

	mesh = LoadMeshOBJ("Resources/rocket.obj");
	meshPos = Vector3f(0.0f, 0.0f, -6.0f);

	_camera.SetPosition({-5.0f, -5.0f, 1.5f});
	_camera.SetUpVector({0.0f, 0.0f, 1.0f});
	_camera.SetViewVector({2.0f, 2.0f, -1.0f});
	_camera.SetPerspective(45.0f, application->GetAspectRatio(), 0.2f, 30.0f);

	shader.Link("Resources/Shaders/Simple.vsh", "Resources/Shaders/Simple.fsh");
}

void TestLayer::onUpdate(float dt)
{
	if( Av::input->KeyPressed(SDL_SCANCODE_RIGHT) )
		meshPos.x += 0.5f * dt;
	if( Av::input->KeyPressed(SDL_SCANCODE_LEFT) )
		meshPos.x -= 0.5f * dt;
	meshAngle += 45.0f * dt;
	if( meshAngle >= 360.0f )
		meshAngle -= 360.0f;
}

void TestLayer::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);

	Matrix4f proj = _camera.GetProjectionMatrix();
	Matrix4f view = _camera.GetViewMatrix();
	Matrix4f model = Matrix4f::Translate(meshPos);
	model *= Matrix4f::Scale({0.2f, 0.2f, 0.2f});
	model *= Matrix4f::Rotate(meshAngle, {0.0f, 0.0f, 1.0f});

	shader.Bind();
	shader.SetUniform("color", Vector4f(0.0f, 1.0f, 1.0f, 1.0f));
	shader.SetUniform("mvp", proj * view * model);

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