#ifndef _AVALANCHE_APP_H_
#define _AVALANCHE_APP_H_

#include "Avalanche.h"

namespace Av
{

class Application
{
public:
	Application();
	~Application();
	
	//implement this to make a game
	virtual void onStart() = 0;
	virtual void onExit() = 0;
	virtual void onUpdate(float diff) {};
	virtual void onKeyDown(int key) {};
	virtual void onKeyUp(int key) {};
	virtual void onMouseDown(int key) {};
	virtual void onMouseUp(int key) {};

	bool Initialize(VideoSettings &settings);
	void Run();

	//misc
	void Shutdown();
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	float GetAspectRatio() const;

private:
	bool ProcessEvents();
	void ProcessEvent(SDL_Event *msg);
	void Exit();
	bool InitWindow(VideoSettings &settings);
	bool InitOpenGL(VideoSettings &settings);

	bool initialized;
	bool running;

	bool minimized;

	int wndWidth;
	int wndHeight;
	float aspect;

	CTimer UpdateTimer;

	SDL_Window *window;
	SDL_GLContext context;

	bool shutdownPlanned;
};

extern Application *application;

} // end of Av namespace

#endif