#include "GameApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"
#include "Graphics.h"

GameApp::GameApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
}

GameApp::~GameApp()
{
}

bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	return true;
}

void GameApp::OnResize()
{
	D3DApp::OnResize();
}

void GameApp::UpdateScene(float dt)
{

}

void GameApp::DrawScene()
{
	static float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };	// RGBA = (0,0,255,255)
	Graphics::GetContext()->ClearRenderTargetView(Graphics::GetRTV().Get(), blue);
	Graphics::GetContext()->ClearDepthStencilView(Graphics::GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	HR(Graphics::GetSwapChain()->Present(0, 0));
}
