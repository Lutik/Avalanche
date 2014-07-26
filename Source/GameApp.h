#pragma once

#include "Avalanche.h"

class AvalancheGame : public Av::Application
{
public:
	AvalancheGame();

	void onStart();

	void onRender();

	void onUpdate(float dt);

	void onKeyDown(int key);

	void onMouseDown(int key);

	void onMouseUp(int key);

	void onExit();

	//unused handlers
	void onKeyUp(int key) {}
};