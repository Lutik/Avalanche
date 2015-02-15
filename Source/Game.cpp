#include "stdafx.h"
#include "Game.h"
#include "ImageLoaders.h"
#include "Utils.h"

GLuint vao;

void TestLayer::SetupGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

TestLayer::TestLayer()
{
	SetupMatrices();
	SetupGL();

	font.Load("Resources/Font/Presquire_32.fnt");

	CheckGLError();

	mesh = font.MakeStringMesh(Vector2f(-0.5f, 0.0f), "Hello, World!", 0.15f);

	font.GetTexture().Bind(0);

	shader.Link("Resources/Shaders/Simple.vsh", "Resources/Shaders/Simple.fsh");
}

void TestLayer::onUpdate(float dt)
{
}

void TestLayer::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);

	shader.Bind();
	shader.SetUniform("tex", 0);
	shader.SetUniform("mvp", GetMVPMatrix());

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

void TestLayer::SetupMatrices()
{
	_modelview.LoadIdentity();

	float aspect = application->GetAspectRatio();
	_projection.LoadIdentity();
	_projection.Ortho2D(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
}

Matrix4f TestLayer::GetMVPMatrix() const
{
	Matrix4f result = _modelview;
	result.MultMatrix(_projection);
	return result;
}