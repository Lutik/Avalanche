#include "stdafx.h"
#include "Game.h"
#include "ImageLoaders.h"
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

	VertexP3 vertData[8] = {
		{{-1.0f, -1.0f, -1.0f}},
		{{-1.0f, -1.0f, 1.0f}},
		{{-1.0f, 1.0f, -1.0f}},
		{{-1.0f, 1.0f, 1.0f}},
		{{1.0f, -1.0f, -1.0f}},
		{{1.0f, -1.0f, 1.0f}},
		{{1.0f, 1.0f, -1.0f}},
		{{1.0f, 1.0f, 1.0f}},
	};
	uint16_t indexData[36] = {
		0, 1, 2,  1, 3, 2,
		0, 2, 4,  4, 2, 6,
		2, 3, 6,  6, 3, 7,
		4, 6, 5,  5, 6, 7,
		1, 0, 4,  5, 4, 1,
		5, 3, 1,  5, 7, 3
	};

	mesh.SetVertices(VertexP3::GetVertexDescription(), 8, vertData);
	mesh.SetIndices(IndexType::SHORT, 36, indexData);

	meshMatrix.LoadIdentity();
	//meshMatrix.Scale(0.3f);

	_camera.SetPosition({-5.0f, -5.0f, 1.5f});
	_camera.SetUpVector({0.0f, 0.0f, 1.0f});
	_camera.SetViewVector({2.0f, 2.0f, -1.0f});
	_camera.SetPerspective(45.0f, application->GetAspectRatio(), 0.2f, 30.0f);

	CheckGLError();

	shader.Link("Resources/Shaders/Simple.vsh", "Resources/Shaders/Simple.fsh");

	CheckGLError("Shader link");
}

void TestLayer::onUpdate(float dt)
{
	meshMatrix.Rotate(10.0f * dt, {1.0f, 0.0f, 0.0f});
	//meshMatrix.Translate({5.0f * dt, 0.0f, 0.0f});
}

void TestLayer::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);
	
	Matrix4f mat;
	mat.LoadIdentity();	
	mat.MultMatrix(_camera.GetProjectionMatrix());
	mat.MultMatrix(_camera.GetViewMatrix());
	mat.MultMatrix(meshMatrix);
	

	shader.Bind();
	shader.SetUniform("color", Vector4f(0.0f, 1.0f, 1.0f, 1.0f));
	shader.SetUniform("mvp", mat);

	mesh.Draw();
}

void TestLayer::onKeyDown(int key)
{
	if(key == SDL_SCANCODE_ESCAPE)
		application->Shutdown();
	else if(key == SDL_SCANCODE_C)
		glClearColor( randf(), randf(), randf(), 1.0f);
}

TestLayer::~TestLayer()
{
}