#include "SamplerState.h"
#include "..\..\ErrorHandle\DXTrace.h"

SamplerState::SamplerState()
{
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));

	// 线性过滤
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(Graphics::GetDevice()->CreateSamplerState(&sampDesc, pSamplerStateLinear.GetAddressOf()));

	//各项异性过滤
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MaxAnisotropy = 4;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(Graphics::GetDevice()->CreateSamplerState(&sampDesc, pSamplerStateAnisotropic.GetAddressOf()));
}

void SamplerState::Bind() const
{
	Graphics::GetContext()->PSSetSamplers(0, 1, pSamplerStateLinear.GetAddressOf());
}

void SamplerState::BindWithType(SamplerStateType Type) const
{
	if (Type == SamplerStateType::LinearWrap)
		Graphics::GetContext()->PSSetSamplers(0, 1, pSamplerStateLinear.GetAddressOf());
	else if (Type == SamplerStateType::AnisotropicWrap)
		Graphics::GetContext()->PSSetSamplers(0, 1, pSamplerStateLinear.GetAddressOf());
}

Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState::pSamplerStateLinear = nullptr;
Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState::pSamplerStateAnisotropic = nullptr;
