#pragma once
#include "Core\Common\d3dApp.h"
#include "Core\Drawable\Box.h"
#include "Core\Drawable\Sphere.h"
#include "Core\Camera\Camera.h"

class GameApp : public D3DApp
{
public:
	struct ConstantBuffer
	{
		DirectX::XMMATRIX world;
	};

public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

private:
	std::unique_ptr<Box> pBox;
	std::unique_ptr<Box> pBox1;
	std::unique_ptr<Sphere> pEarth;
	std::unique_ptr<Sphere> pMoon;
	std::unique_ptr<Sphere> pSun;

	std::unique_ptr<FirstPersonCamera> pCam;

	//std::vector<std::unique_ptr<class Drawable>> drawables;
};
