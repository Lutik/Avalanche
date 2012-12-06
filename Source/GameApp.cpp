#include "stdafx.h"
#include "GameApp.h"

void AvalancheGame::onStart()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void AvalancheGame::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void AvalancheGame::onUpdate(float diff)
{
}

void AvalancheGame::onKeyDown(int key)
{
	if(key == SDL_SCANCODE_ESCAPE)
		Shutdown();
}

void AvalancheGame::onMouseDown(int key)
{
}

void AvalancheGame::onMouseUp(int key)
{
}

void AvalancheGame::onExit()
{
}