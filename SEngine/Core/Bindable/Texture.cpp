#include "Texture.h"
#include "..\ErrorHandle\DXTrace.h"
#include "..\..\Dependencies\DirectXTex\DDSTextureLoader\DDSTextureLoader11.h"
#include "..\..\Dependencies\DirectXTex\WICTextureLoader\WICTextureLoader11.h"
#include <cwchar>

Texture::Texture(const wchar_t* TexPath)
{
	const wchar_t* dds = L".dds";
	const wchar_t* jpg = L".jpg";
	if (wcsstr(TexPath, dds))
	{
		HR(DirectX::CreateDDSTextureFromFile(Graphics::GetDevice().Get(), TexPath, nullptr, pTexture.GetAddressOf()));
	}
	else if (wcsstr(TexPath, jpg))
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


