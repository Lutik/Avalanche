#include "stdafx.h"
#include "GameApp.h"

#include "ImageLoaders.h"
#include "VertexBuffer.h"

DeviceBuffer<GL_ARRAY_BUFFER, VertexP2T2> vb;

void AvalancheGame::onStart()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	VertexP2T2 buf[32];
	for(int i = 0; i < 32; ++i)
	{
		buf[i].pos = Vector2f(randf(), randf());
		buf[i].uv = Vector2f(randf(), randf());
	}
	vb.Init(32, buf);
}

void AvalancheGame::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vb.Bind();

	vb.Unbind();
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
	vb.Release();
}