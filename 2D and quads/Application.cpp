#include "Application.h"

Application::Application()
{
	graphics = 0;
}

Application::~Application()
{

}

bool Application::Initialize()
{
	int windowWidth, windowHeight;

	//Initialize Windows

	if (!InitializeWindows(windowWidth, windowHeight))
		return false;

	//--

	// Initialize all subsystems (Graphics, input etc)

	graphics = new Graphics();

	if (!graphics)
	{
		return false;
	}

	if (!graphics->Initialize(windowWidth, windowHeight, mHwnd))
	{
		return false;
	}

	//--

	return true;
}

LRESULT CALLBACK Application::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_KEYDOWN:
			MessageBox(NULL, "keydown", "key", MB_OK);

		default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}


void Application::Run()
{
	MSG msg = { 0 };

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			// Run frames
			Frame();
		}
	}
}

void Application::Shutdown()
{
	if (graphics)
	{
		delete graphics;
		graphics = 0;
	}
	ShutdownWindows();
}

void Application::ShutdownWindows()
{
	DestroyWindow(mHwnd);
	mHwnd = NULL;

	UnregisterClass(applicationName, hinstance);
	hinstance = NULL;

	applicationHandle = NULL;


}

bool Application::InitializeWindows(int &width, int&height)
{
	WNDCLASSEX wc;
	int posX, posY;

	applicationHandle = this;

	applicationName = "GameDevelopment";

	hinstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		// Some kind of special error handling?

		MessageBox(NULL, "Error registering the window class.", "Windows Error", MB_OK);
		return false;
	}

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	width = 800;
	height = 600;

	posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;


	mHwnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, width, height, NULL, NULL, hinstance, NULL);

	if (!mHwnd)
	{
		MessageBox(NULL, "Error creating window", "Windows Error", MB_OK);
		return false;
	}

	ShowWindow(mHwnd, SW_SHOW);
	SetForegroundWindow(mHwnd);
	UpdateWindow(mHwnd);

	return true;
}

bool Application::Frame()
{
	if (!graphics->Frame())
	{
		return false;
	}
	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		default: applicationHandle->MessageHandler(hwnd, msg, wParam, lParam);
	}
	return 0;
}