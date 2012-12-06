#include "stdafx.h"
#include "GameApp.h"

AvalancheGame app;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	VideoSettings v;
	v.fullscreen = false;
	v.width = 1024;
	v.height = 600;

	if(app.Initialize(v))
		app.Run();

	return 0;
}