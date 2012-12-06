#include "stdafx.h"
#include "Input.h"

namespace Av
{

Input *input = nullptr;

Input::Input(SDL_Window *wnd, int width, int height)
	: window(wnd)
	, wndWidth(width)
	, wndHeight(height)
{
	mouseGrabbed = false;
	mouseVisible = true;
}

Input::~Input()
{
}

bool Input::IsMouseGrabbed() const
{
	return mouseGrabbed;
}

void Input::GrabMouse(bool grabbed)
{
	if(mouseGrabbed == grabbed) return;

	mouseGrabbed = grabbed;
	mousedx = 0;
	mousedy = 0;
	if(grabbed)
	{
		old_mousex = mousex;
		old_mousey = mousey;
		mousex = wndWidth/2;
		mousey = wndHeight/2;
		SDL_WarpMouseInWindow(window, mousex, mousey);
	}
	else
	{
		mousex = old_mousex;
		mousey = old_mousey;
		SDL_WarpMouseInWindow(window, mousex, mousey);
	}
}

void Input::UpdateMouseState()
{
	int x,y;
	mouseState = SDL_GetMouseState(&x, &y);
	if(mouseGrabbed)
	{
		mousex = wndWidth/2;
		mousey = wndHeight/2;
		mousedx = x - mousex;
		mousedy = y - mousey;
		SDL_WarpMouseInWindow(window, mousex, mousey);
	}
	else
	{
		mousex = x;
		mousey = y;
		mousedx = 0;
		mousedy = 0;
	}
}

void Input::ShowMouse(bool show)
{
	if(mouseVisible != show)
	{
		mouseVisible = show;
		SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
	}
}

bool Input::KeyPressed(int key)
{
	return (keyStates[key] != 0);
}

bool Input::MousePressed(int key)
{
	return ((mouseState & SDL_BUTTON(key)) != 0);
}

void Input::UpdateKeyStates()
{
	keyStates = SDL_GetKeyboardState(nullptr);
}

bool Input::IsMouseVisible() const
{
	return mouseVisible;
}

int Input::GetMouseX() const
{
	return mousex;
}

int Input::GetMouseY() const
{
	return mousey;
}

float Input::fGetMouseX() const
{
	return float(2*mousex - wndWidth) / float(wndHeight);
}

float Input::fGetMouseY() const
{
	return float(wndHeight-2*mousey) / float(wndHeight);
}

int Input::GetMouseDX() const
{
	return mousedx;
}

int Input::GetMouseDY() const
{
	return mousedy;
}

} // end of Av namespace