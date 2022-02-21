#include "DepthStencilState.h"
#include "..\..\ErrorHandle\DXTrace.h"

DepthStencilState::DepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC dsDesc;

	// 用于绘制天空盒
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dsDesc.StencilEnable = false;
	HR(Graphics::GetDevice()->CreateDepthStencilState(&dsDesc, pDepthStencilStateLessEqual.GetAddressOf()));
}

void DepthStencilState::Bind() const
{
	Graphics::GetContext()->OMSetDepthStencilState(pDepthStencilStateLessEqual.Get(), 0);
}

Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilStateLessEqual = nullptr;