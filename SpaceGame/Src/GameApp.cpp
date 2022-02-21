#include "GameApp.h"
#include "Core\Common\d3dUtil.h"
#include "DXTrace.h"
using namespace DirectX;

GameApp::GameApp(HINSTANCE hInstance)
	: 
	D3DApp(hInstance),
	pCam(nullptr),
	pEarth(nullptr),
	pMoon(nullptr),
	pSun(nullptr)
{
}

GameApp::~GameApp()
{
}

bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	pCam = std::make_unique<FirstPersonCamera>();
	pCam->LookAt({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f });
	pCam->ActiveCamera();

	pEarth = std::make_unique<Sphere>(1.0f, 20, 20, L"Texture\\Earth.jpg");
	pEarth->trans.SetPosition(0.0f, 0.0f, 5.0f);
	pMoon = std::make_unique<Sphere>(5.0f, 20, 20, L"Texture\\Moon.png");
	pMoon->trans.SetPosition(5.0f, 0.0f, 5.0f);
	pSun = std::make_unique<Sphere>(8.0f, 20, 20, L"Texture\\Sun.jpg");
	pSun->trans.SetPosition(-10.0f, 0.0f, 10.0f);

	m_pMouse->SetWindow(m_hMainWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);

	return true;
}

void GameApp::OnResize()
{
	D3DApp::OnResize();
}

void GameApp::UpdateScene(float dt)
{
	float cubePhi = 0.0f, cubeTheta = 0.0f;
	// 获取鼠标状态
	Mouse::State mouseState = m_pMouse->GetState();
	Mouse::State lastMouseState = m_MouseTracker.GetLastState();
	// 获取键盘状态
	Keyboard::State keyState = m_pKeyboard->GetState();
	Keyboard::State lastKeyState = m_KeyboardTracker.GetLastState();

	// 更新鼠标按钮状态跟踪器，仅当鼠标按住的情况下才进行移动
	m_MouseTracker.Update(mouseState);
	m_KeyboardTracker.Update(keyState);
	if (mouseState.leftButton == true && m_MouseTracker.leftButton == m_MouseTracker.HELD)
	{
		cubeTheta -= (mouseState.x - lastMouseState.x) * 0.01f;
		cubePhi -= (mouseState.y - lastMouseState.y) * 0.01f;
	}

	if (keyState.IsKeyDown(Keyboard::W))
		pEarth->trans.Translate({ 0.0f, 0.0f, 1.0f }, 0.01f);
	if (keyState.IsKeyDown(Keyboard::S))
		pEarth->trans.Translate({ 0.0f, 0.0f, 1.0f }, -0.01f);
	if (keyState.IsKeyDown(Keyboard::A))
		pEarth->trans.Translate({ 1.0f, 0.0f, 0.0f }, -0.01f);
	if (keyState.IsKeyDown(Keyboard::D))
		pEarth->trans.Translate({ 1.0f, 0.0f, 0.0f }, 0.01f);
}

void GameApp::DrawScene()
{
	static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,0,255)
	Graphics::GetContext()->ClearRenderTargetView(Graphics::GetRTV().Get(), reinterpret_cast<const float*>(&black));
	Graphics::GetContext()->ClearDepthStencilView(Graphics::GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	pEarth->Draw();
	pMoon->Draw();
	pSun->Draw();

	HR(Graphics::GetSwapChain()->Present(0, 0));
}

