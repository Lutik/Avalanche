#include "stdafx.h"
#include "Application.h"
#include "Log.h"

namespace Av
{

const char *PROGRAM_NAME = "AvalancheSDL";

Application *application = nullptr;

Application::Application()
	: window(nullptr)
{
	initialized = false;
	running = false;
	shutdownPlanned = false;
	minimized = false;

	application = this;
}

Application::~Application()
{
}

bool Application::InitWindow(VideoSettings &settings)
{
	wndWidth = settings.width;
	wndHeight = settings.height;
	aspect = (float) wndWidth / (float) wndHeight;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		wndWidth, wndHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if( !window )
	{
		Log::log("Failed to create window\n");
		return false;
	}
	
	input = new Input(window, wndWidth, wndHeight);

	return true;
}

bool Application::InitOpenGL(VideoSettings &settings)
{
	context = SDL_GL_CreateContext(window);

	int majorVersion, minorVersion;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersion);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersion);

	Log::log("Created OpenGL context %d.%d\n", majorVersion, minorVersion);

	return (ogl_LoadFunctions() != ogl_LOAD_FAILED);
}

bool Application::Initialize(VideoSettings &settings)
{
	if(initialized) return false;

	Log::open("engine.txt", true);
	Log::log("Launching Avalanche Engine 2\n");
	Log::log("Build date: "__DATE__", "__TIME__"\n\n");

	if(SDL_Init(SDL_INIT_VIDEO /*| SDL_INIT_TIMER*/) < 0)
	{
		Log::log("Error: SDL_Init failed\n");
		return false;
	}

	if(!InitWindow(settings)) return false;
	if(!InitOpenGL(settings)) return false;

	initialized = true;

	return initialized;
}

void Application::Exit()
{
	if(!initialized) return;

	onExit();

	Log::log("Shutting down...");
	Log::close();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);

	if( input )
	{
		delete input;
		input = nullptr;
	}

	SDL_Quit();

	initialized = false;
}

void Application::Run()
{
	if(running) return;

	running = true;

	onStart();

	UpdateTimer.Start();

	while(!shutdownPlanned)
	{
		ProcessEvents();
		float diff = UpdateTimer.GetTime(true);
		if(!minimized)
		{
			//SDL_PumpEvents();
			input->UpdateMouseState();
			input->UpdateKeyStates();

			onUpdate(diff);
			onRender();
			SDL_GL_SwapWindow(window);
		}
	}

	running = false;
	
	Exit();
}

bool Application::ProcessEvents()
{
	SDL_Event msg;
	while(SDL_PollEvent(&msg))
	{
		ProcessEvent(&msg);
	}
	return true;
}

void Application::ProcessEvent(SDL_Event *msg)
{
	switch(msg->type)
	{
		case SDL_QUIT: Shutdown(); return;
		case SDL_KEYDOWN: onKeyDown(msg->key.keysym.scancode); return;
		case SDL_KEYUP: onKeyUp(msg->key.keysym.scancode); return;
		case SDL_MOUSEBUTTONDOWN: onMouseDown(msg->button.button); return;
		case SDL_MOUSEBUTTONUP: onMouseUp(msg->button.button); return;
	}
}

void Application::Shutdown()
{
	shutdownPlanned = true;
}

int Application::GetWindowWidth() const
{
	return wndWidth;
}

int Application::GetWindowHeight() const
{
	return wndHeight;
}

float Application::GetAspectRatio() const
{
	return aspect;
}

} // end of Av namespace