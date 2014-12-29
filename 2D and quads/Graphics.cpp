#include "Graphics.h"

Graphics::Graphics()
{
	m_D3D = 0;
}

Graphics::~Graphics()
{
}

void Graphics::Shutdown()
{
	if (m_D3D)
	{
		delete m_D3D;
		m_D3D = 0;
	}
}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	m_D3D = new D3DClass;

	if (!m_D3D)
		return false;

	if (!m_D3D->Initialize(screenWidth, screenHeight, false, hwnd, true))
	{
		MessageBox(NULL, "Could not initialize direct3d", "ERROR", MB_OK);
		return false;
	}

	return true;
}

bool Graphics::Frame()
{
	return Render();
}

bool Graphics::Render()
{
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	m_D3D->EndScene();

	return true;
}