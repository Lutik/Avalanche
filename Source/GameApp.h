#pragma once

#include "Avalanche.h"

class AvalancheGame : public Av::Application
{
	Matrix4f _modelview;
	Matrix4f _projection;

	void SetupMatrices();
	void SetupGL();

	Matrix4f GetMVPMatrix() const;
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