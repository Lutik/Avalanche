#pragma once

class Scene
{
public:
	virtual ~Scene() {};

	virtual void onRender() = 0;
	virtual void onUpdate(float dt) = 0;
	virtual void onKeyDown(int key) {};
	virtual void onKeyUp(int key) {};
	virtual void onMouseDown(int key) {};
	virtual void onMouseUp(int key) {};

	typedef std::unique_ptr<Scene> Ptr;
};