#include "DepthStencilState.h"
#include "..\..\ErrorHandle\DXTrace.h"

DepthStencilState::DepthStencilState(DepthStencilStateType Type)
	:
	Type(Type)
{
	D3D11_DEPTH_STENCIL_DESC dsDesc;

	// 用于绘制天空盒
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dsDesc.StencilEnable = false;
	HR(Graphics::GetDevice()->CreateDepthStencilState(&dsDesc, pDepthStencilStateLessEqual.GetAddressOf()));

	// 进行深度测试，但不写入深度值的状态
	// 若绘制非透明物体时，应使用默认状态
	// 绘制透明物体时，使用该状态可以有效确保混合状态的进行
	// 并且确保较前的非透明物体可以阻挡较后的一切物体
	// 对满足模板值条件的区域才进行绘制
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
	// 对于背面的几何体我们是不进行渲染的，所以这里的设置无关紧要
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;

	HR(Graphics::GetDevice()->CreateDepthStencilState(&dsDesc, pDepthStencilStateNoDepthWriteWithStencil.GetAddressOf()));
}

void DepthStencilState::Bind() const
{
	if (Type == DepthStencilStateType::LessEqual)
		Graphics::GetContext()->OMSetDepthStencilState(pDepthStencilStateLessEqual.Get(), 0);
	else if (Type == DepthStencilStateType::NoDepthWriteWithStencil)
		Graphics::GetContext()->OMSetDepthStencilState(pDepthStencilStateNoDepthWriteWithStencil.Get(), 0);
}

Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilState::pDepthStencilStateLessEqual = nullptr;
Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilState::pDepthStencilStateNoDepthWriteWithStencil = nullptr;