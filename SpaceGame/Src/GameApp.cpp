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
	pSun(nullptr),
	pSkyBox(nullptr)
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
	pCam->LookAt({ 0.0f, 0.0f, -15.0f }, { 0.0f, 0.0f, 0.0f });
	pCam->ActiveCamera();

	pEarth = std::make_unique<Sphere>(5.0f, 20, 20, L"Texture\\Earth.jpg");
	pEarth->trans.SetPosition(5.0f, 0.0f, 5.0f);
	pMoon = std::make_unique<Sphere>(3.0f, 20, 20, L"Texture\\Moon.png");
	pMoon->trans.SetPosition(15.0f, 0.0f, 5.0f);
	pSun = std::make_unique<Sphere>(10.0f, 20, 20, L"Texture\\Sun.jpg");
	pSun->trans.SetPosition(-20.0f, 0.0f, 10.0f);
	pSkyBox = std::make_unique<SkyBox>(
		std::vector<std::wstring>{
		L"Texture\\SkyBox\\sunset_posX.bmp", L"Texture\\SkyBox\\sunset_negX.bmp",
		L"Texture\\SkyBox\\sunset_posY.bmp", L"Texture\\SkyBox\\sunset_negY.bmp",
		L"Texture\\SkyBox\\sunset_posZ.bmp", L"Texture\\SkyBox\\sunset_negZ.bmp", }
		);

	m_pMouse->SetWindow(m_hMainWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_RELATIVE);

	return true;
}

void GameApp::OnResize()
{
	D3DApp::OnResize();
}

void GameApp::UpdateScene(float dt)
{
	// 更新鼠标事件，获取相对偏移量
	Mouse::State mouseState = m_pMouse->GetState();
	Mouse::State lastMouseState = m_MouseTracker.GetLastState();

	Keyboard::State keyState = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keyState);

	// 第一人称/自由摄像机的操作

	// 方向移动
	if (keyState.IsKeyDown(Keyboard::W))
		pCam->Walk(dt * 6.0f);
	if (keyState.IsKeyDown(Keyboard::S))
		pCam->Walk(dt * -6.0f);
	if (keyState.IsKeyDown(Keyboard::A))
		pCam->Strafe(dt * -6.0f);
	if (keyState.IsKeyDown(Keyboard::D))
		pCam->Strafe(dt * 6.0f);

	//// 将摄像机位置限制在[-8.9, 8.9]x[-8.9, 8.9]x[0.0, 8.9]的区域内
	//// 不允许穿地
	//XMFLOAT3 adjustedPos;
	//XMStoreFloat3(&adjustedPos, XMVectorClamp(pCam->GetPositionXM(), XMVectorSet(-8.9f, 0.0f, -8.9f, 0.0f), XMVectorReplicate(8.9f)));
	//pCam->SetPosition(adjustedPos);

	// 在鼠标没进入窗口前仍为ABSOLUTE模式
	if (mouseState.positionMode == Mouse::MODE_RELATIVE)
	{
		pCam->Pitch(mouseState.y * dt * 2.5f);
		pCam->RotateY(mouseState.x * dt * 2.5f);
	}

	pCam->Update();

	// esc 退出
	if (keyState.IsKeyDown(Keyboard::Escape))
		SendMessage(MainWnd(), WM_DESTROY, 0, 0);
}

void GameApp::DrawScene()
{
	static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,0,255)
	Graphics::GetContext()->ClearRenderTargetView(Graphics::GetRTV().Get(), reinterpret_cast<const float*>(&black));
	Graphics::GetContext()->ClearDepthStencilView(Graphics::GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	pEarth->Draw();
	pMoon->Draw();
	pSun->Draw();
	pSkyBox->Draw();

	HR(Graphics::GetSwapChain()->Present(0, 0));
}

