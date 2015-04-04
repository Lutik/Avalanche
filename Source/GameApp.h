#pragma once

#include "Avalanche.h"

#include "Scene.h"

class AvalancheGame : public Av::Application
{
	std::unique_ptr<Scene> _game;

	void SetupGL();
public:
	AvalancheGame();

	void onStart() override;
	void onRender() override;
	void onUpdate(float dt) override;
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseDown(int key) override;
	void onMouseUp(int key) override;
	void onExit() override;
};