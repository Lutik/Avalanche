#include "stdafx.h"
#include "GameApp.h"

#include "ImageLoaders.h"
#include "VertexBuffer.h"
#include "VertexTypes.h"
#include "Shader.h"

VertexBuffer<VertexP2T2> vb;
ShaderProgram shader;
GLuint vao;
Matrix4f projection;

AvalancheGame::AvalancheGame()
{
}

void AvalancheGame::SetupGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void AvalancheGame::onStart()
{
	SetupMatrices();
	SetupGL();

	VertexP2T2 v[] =
	{
		{ { -0.5f, 0.5f }, { 0.0f, 1.0f } },
		{ { -0.5f, -0.5f }, { 0.0f, 0.0f } },
		{ { 0.5f, 0.5f }, { 1.0f, 1.0f } },
		{ { 0.5f, -0.5f }, { 1.0f, 0.0f } }
	};
	vb.Init(4, v, GL_STATIC_DRAW);
	vb.Bind();

	int w, h;
	GLuint texID = loadTexture("Resources/energy_dust.png", w, h);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	shader.Init("Resources/Shaders/Simple.vsh", "Resources/Shaders/Simple.fsh");

	GLint posLoc = glGetAttribLocation(shader.GetID(), "in_pos");
	glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexP2T2), (GLvoid*)offsetof(VertexP2T2, pos));
	glEnableVertexAttribArray(posLoc);

	GLint uvLoc = glGetAttribLocation(shader.GetID(), "in_uv");
	glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexP2T2), (GLvoid*)offsetof(VertexP2T2, uv));
	glEnableVertexAttribArray(uvLoc);
}

void AvalancheGame::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Bind();
	glBindVertexArray(vao);

	GLuint texLoc = glGetUniformLocation(shader.GetID(), "tex");
	glUniform1i(texLoc, 0);

	GLuint mvpLoc = glGetUniformLocation(shader.GetID(), "mvp");
	Matrix4f mvp = GetMVPMatrix();
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp.ptr());

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void AvalancheGame::onUpdate(float dt)
{
}

void AvalancheGame::onKeyDown(int key)
{
	if(key == SDL_SCANCODE_ESCAPE)
		Shutdown();
	else if(key == SDL_SCANCODE_C)
		glClearColor( randf(), randf(), randf(), 1.0f);
}

void AvalancheGame::onMouseDown(int key)
{
}

void AvalancheGame::onMouseUp(int key)
{
}

void AvalancheGame::onExit()
{
	shader.Release();
	vb.Release();
}


void AvalancheGame::SetupMatrices()
{
	_modelview.LoadIdentity();

	float aspect = GetAspectRatio();
	_projection.LoadIdentity();
	_projection.Ortho2D(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
}

Matrix4f AvalancheGame::GetMVPMatrix() const
{
	Matrix4f result = _modelview;
	result.MultMatrix(_projection);
	return result;
}