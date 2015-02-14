#include "stdafx.h"
#include "GameApp.h"
#include "Game.h"


Av::Application *IGameLayer::application = nullptr;

AvalancheGame::AvalancheGame()
{
	IGameLayer::application = this;
}

void AvalancheGame::onStart()
{
	_game.reset(new TestLayer());
}

void AvalancheGame::onRender()
{
	_game->onRender();
}

void AvalancheGame::onUpdate(float dt)
{
	_game->onUpdate(dt);
}

void AvalancheGame::onKeyDown(int key)
{
	_game->onKeyDown(key);
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
}