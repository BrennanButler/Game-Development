#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "Graphics.h"

class Application {

public:
	Application();
	~Application();

public:
	bool Initialize();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Shutdown();

private:
	bool Frame();
	bool InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	HWND mHwnd;
	LPCSTR applicationName;
	HINSTANCE hinstance;
	Graphics *graphics;
};


static Application *applicationHandle = 0;
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif