#include "RasterizerState.h"
#include "..\..\ErrorHandle\DXTrace.h"

RasterizerState::RasterizerState(RasterizerStateType Type)
	:
	Type(Type)
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

	// 无背面剔除模式
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.DepthClipEnable = true;
	HR(Graphics::GetDevice()->CreateRasterizerState(&rasterizerDesc, pRasterizerStateNoCull.GetAddressOf()));

	//背面剔除模式
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.DepthClipEnable = true;
	HR(Graphics::GetDevice()->CreateRasterizerState(&rasterizerDesc, pRasterizerStateBackCull.GetAddressOf()));
}

void RasterizerState::Bind() const
{
	if (Type == RasterizerStateType::NoCull)
		Graphics::GetContext()->RSSetState(pRasterizerStateNoCull.Get());
	else if (Type == RasterizerStateType::BackCull)
		Graphics::GetContext()->RSSetState(pRasterizerStateBackCull.Get());
}

Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState::pRasterizerStateNoCull = nullptr;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState::pRasterizerStateBackCull = nullptr;