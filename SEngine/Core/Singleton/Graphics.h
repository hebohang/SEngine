#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include "..\..\d3dApp.h"

class Graphics
{
	friend class D3DApp;

	template <class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	static Graphics& GetInstance()
	{
		static Graphics instance(hWnd);
		return instance;
	}
public:
	static D3D11_VIEWPORT& GetVp()
	{
		return GetInstance().ScreenViewport;
	}
	static ComPtr<ID3D11Device>& GetDevice()
	{
		return GetInstance().pDevice;
	}
	static ComPtr<IDXGISwapChain>& GetSwapChain()
	{
		return GetInstance().pSwap;
	}
	static ComPtr<ID3D11DeviceContext>& GetContext()
	{
		return GetInstance().pContext;
	}
	static ComPtr<ID3D11RenderTargetView>& GetRTV()
	{
		return GetInstance().pTarget;
	}	
	static ComPtr<ID3D11DepthStencilView>& GetDSV()
	{
		return GetInstance().pDSV;
	}
	static ComPtr<ID3D11Texture2D>& GetDSBuffer()
	{
		return GetInstance().pDepthStencilBuffer;
	}
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics(Graphics&&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	Graphics& operator=(Graphics&&) = delete;
public:
	static HWND hWnd;
private:
	D3D11_VIEWPORT ScreenViewport;
	ComPtr<ID3D11Device> pDevice;
	ComPtr<IDXGISwapChain> pSwap;
	ComPtr<ID3D11DeviceContext> pContext;
	ComPtr<ID3D11RenderTargetView> pTarget;
	ComPtr<ID3D11DepthStencilView> pDSV;
	ComPtr<ID3D11Texture2D> pDepthStencilBuffer;				// 深度模板缓冲区

	// Direct3D 11
	ComPtr<ID3D11Device> m_pd3dDevice;							    // D3D11设备
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;			    // D3D11设备上下文
	ComPtr<IDXGISwapChain> m_pSwapChain;							// D3D11交换链
	// Direct3D 11.1
	ComPtr<ID3D11Device1> m_pd3dDevice1;							// D3D11.1设备
	ComPtr<ID3D11DeviceContext1> m_pd3dImmediateContext1;			// D3D11.1设备上下文
	ComPtr<IDXGISwapChain1> m_pSwapChain1;						    // D3D11.1交换链
	// 常用资源
	ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;					// 深度模板缓冲区
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;				// 渲染目标视图
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;				// 深度模板视图
	D3D11_VIEWPORT m_ScreenViewport;								// 视口
};
