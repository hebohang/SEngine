#pragma once
#include "Core\Common\d3dApp.h"
#include "Core\Drawable\Box.h"

class GameApp : public D3DApp
{
public:
	struct ConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX proj;
	};

public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

private:
	bool InitResource();

private:
	std::unique_ptr<Box> box;
	//std::vector<std::unique_ptr<class Drawable>> drawables;

	ComPtr<ID3D11Buffer> m_pConstantBuffer;		    // 常量缓冲区

	ConstantBuffer m_CBuffer;	                    // 用于修改GPU常量缓冲区的变量
};
