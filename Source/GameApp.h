#pragma once

#include "Avalanche.h"

class IScene
{
public:
	virtual ~IScene() {};

	virtual void onRender() = 0;
	virtual void onUpdate(float dt) = 0;
	virtual void onKeyDown(int key) {};
	virtual void onKeyUp(int key) {};
	virtual void onMouseDown(int key) {};
	virtual void onMouseUp(int key) {};

	typedef std::unique_ptr<IScene> Ptr;
};

class AvalancheGame : public Av::Application
{
	IScene::Ptr _game;
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