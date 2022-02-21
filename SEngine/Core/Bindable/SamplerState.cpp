#include "SamplerState.h"
#include "..\ErrorHandle\DXTrace.h"

SamplerState::SamplerState()
{
	D3D11_SAMPLER_DESC sampDesc;
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(Graphics::GetDevice()->CreateSamplerState(&sampDesc, pSamplerState.GetAddressOf()));
}

void SamplerState::Bind() const
{
	Graphics::GetContext()->PSSetSamplers(0, 1, pSamplerState.GetAddressOf());
}