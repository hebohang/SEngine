#include "Texture.h"
#include "..\ErrorHandle\DXTrace.h"
#include "..\..\Dependencies\DirectXTex\DDSTextureLoader\DDSTextureLoader11.h"
#include "..\..\Dependencies\DirectXTex\WICTextureLoader\WICTextureLoader11.h"
#include <cwchar>

Texture::Texture(const wchar_t* TexPath)
{
	const wchar_t* dds = L".dds";
	const wchar_t* jpg = L".jpg";
	const wchar_t* png = L".png";
	if (wcsstr(TexPath, dds))
	{
		HR(DirectX::CreateDDSTextureFromFile(Graphics::GetDevice().Get(), TexPath, nullptr, pTexture.GetAddressOf()));
	}
	else if (wcsstr(TexPath, jpg) || wcsstr(TexPath, png))
	{
		HR(DirectX::CreateWICTextureFromFile(Graphics::GetDevice().Get(), TexPath, nullptr, pTexture.GetAddressOf()));
	}
}

void Texture::Bind() const
{
	Graphics::GetContext()->PSSetShaderResources(0, 1, pTexture.GetAddressOf());
}

void Texture::BindToSlot(UINT slot) const
{
	Graphics::GetContext()->PSSetShaderResources(slot, 1, pTexture.GetAddressOf());
}


