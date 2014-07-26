#include "stdafx.h"
#include "GameApp.h"

#include "ImageLoaders.h"
#include "VertexBuffer.h"
#include "VertexTypes.h"
#include "Shader.h"

VertexBuffer<VertexP2T2> vb;
ShaderProgram shader;
GLuint vao;

AvalancheGame::AvalancheGame()
{
}

void AvalancheGame::onStart()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	VertexP2T2 v[3] =
	{
		{ { -0.5f, -0.5f }, { 0.0f, 0.0f } },
		{ { -0.5f, 0.5f }, { 0.0f, 1.0f } },
		{ { 0.5f, 0.5f }, { 1.0f, 1.0f } }
	};
	vb.Init(3, v, GL_STATIC_DRAW);
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

	glDrawArrays(GL_TRIANGLES, 0, 3);
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