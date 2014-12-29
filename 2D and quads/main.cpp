#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Application *app;

	app = new Application();

	if (!app)
	{
		return 0;
	}

	if (app->Initialize())
	{
		app->Run();
	}

	app->Shutdown();

	delete app;
	app = 0;
	return 0;
}