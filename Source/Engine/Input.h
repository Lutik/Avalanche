#ifndef _AVALANCHE_INPUT_H_
#define _AVALANCHE_INPUT_H_

namespace Av
{

class Input
{
public:
	//keyboard functions
	bool KeyPressed(int key);
	bool MousePressed(int key);

	//cursor functions
	void GrabMouse(bool grabbed);
	bool IsMouseGrabbed() const;
	void ShowMouse(bool show);
	bool IsMouseVisible() const;
	int GetMouseX() const;
	int GetMouseY() const;
	float fGetMouseX() const;
	float fGetMouseY() const;
	int GetMouseDX() const;
	int GetMouseDY() const;

// INTERNAL (make private and make App&Input friends?)
	Input(SDL_Window *window, int width, int height);
	~Input();
	void UpdateKeyStates();
	void UpdateMouseState();
private:
	SDL_Window *window;
	int wndWidth, wndHeight;

	int mousex, mousey, mousedx, mousedy, old_mousex, old_mousey;
	bool mouseGrabbed;
	bool mouseVisible;
	Uint8 *keyStates;
	Uint8 mouseState;
};

extern Input *input;

} // end of Av namespace

#endif