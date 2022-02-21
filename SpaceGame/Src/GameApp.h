#pragma once
#include "Core\Common\d3dApp.h"
#include "Core\Drawable\Box.h"
#include "Core\Drawable\Sphere.h"
#include "Core\Drawable\SkyBox.h"
#include "Core\Camera\Camera.h"

class GameApp : public D3DApp
{
public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

private:
	std::unique_ptr<FirstPersonCamera> pCam;

	std::unique_ptr<Sphere> pEarth;
	std::unique_ptr<Sphere> pMoon;
	std::unique_ptr<Sphere> pSun;

	std::unique_ptr<SkyBox> pSkyBox;
};
