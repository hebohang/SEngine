#include "Texture.h"
#include "..\ErrorHandle\DXTrace.h"
#include "..\Common\d3dUtil.h"
#include "..\..\Dependencies\DirectXTex\DDSTextureLoader\DDSTextureLoader11.h"
#include "..\..\Dependencies\DirectXTex\WICTextureLoader\WICTextureLoader11.h"
#include <cwchar>

Texture::Texture(const wchar_t* TexPath)
{
	assert(TexPath);

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

Texture::Texture(const std::vector<std::wstring>& CubMapPath)
{
	assert(CubMapPath.size());

	const wchar_t* jpg = L".jpg";
	const wchar_t* png = L".png";
	const wchar_t* bmp = L".bmp";
	if (wcsstr(CubMapPath[0].c_str(), jpg) || wcsstr(CubMapPath[0].c_str(), png) || wcsstr(CubMapPath[0].c_str(), bmp))
	{
		HR(CreateWICTexture2DCubeFromFile(Graphics::GetDevice().Get(), Graphics::GetContext().Get(), CubMapPath, nullptr, pTexture.GetAddressOf(), false));
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


