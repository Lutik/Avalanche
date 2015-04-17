#include "stdafx.h"
#include "GameApp.h"
#include "Game.h"
#include "ResourceManager.h"


AvalancheGame::AvalancheGame()
{
}

void AvalancheGame::SetupGL()
{
	glClearColor(0.0f, 0.0f, 0.05f, 1.0f);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_CULL_FACE);
}

void AvalancheGame::onStart()
{
	Av::resourceManager.LoadDescriptions("Resources/resources.json");
	Av::resourceManager.LoadResources();

	SetupGL();

	_game.reset(new TestScene());
}

void AvalancheGame::onUpdate(float dt)
{
	_game->onUpdate(dt);
}

void AvalancheGame::onKeyDown(int key)
{
	if (key == SDL_SCANCODE_ESCAPE) {
		Av::application->Shutdown();
	} else {
		_game->onKeyDown(key);
	}
}

void AvalancheGame::onKeyUp(int key)
{
	_game->onKeyUp(key);
}

void AvalancheGame::onMouseDown(int key)
{
	_game->onMouseDown(key);
}

void AvalancheGame::onMouseUp(int key)
{
	_game->onMouseUp(key);
}

void AvalancheGame::onExit()
{
	_game.reset();
	Av::resourceManager.UnloadResources();
}