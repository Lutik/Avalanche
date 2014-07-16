#include "stdafx.h"
#include "GameApp.h"

#include "ImageLoaders.h"
#include "VertexBuffer.h"
#include "VertexTypes.h"
#include "Shader.h"

VertexBuffer<Vector2f> vb;
ShaderProgram shader;
GLuint vao;

void AvalancheGame::onStart()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Vector2f v[3];
	v[0] = Vector2f(-0.5f, -0.5f);
	v[1] = Vector2f(0.5f, -0.5f);
	v[2] = Vector2f(0.0f, 0.5f);
	vb.Init(3, v, GL_STATIC_DRAW);
	vb.Bind();

	shader.Init("Resources/Shaders/Simple.vsh", "Resources/Shaders/Simple.fsh");

	GLint attrLoc = glGetAttribLocation(shader.GetID(), "position");
	glVertexAttribPointer(attrLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2f), NULL);
	glEnableVertexAttribArray(attrLoc);
}

void AvalancheGame::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Bind();
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void AvalancheGame::onUpdate(float diff)
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