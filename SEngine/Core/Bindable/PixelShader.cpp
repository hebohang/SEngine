#include "PixelShader.h"
#include "..\ErrorHandle\DXTrace.h"
#include "..\Common\d3dUtil.h"

PixelShader::PixelShader(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName, LPCSTR entryPoint, LPCSTR shaderModel)
	:
	pBlob(nullptr),
	pPixelShader(nullptr)
{
	HR(CreateShaderFromFile(csoFileNameInOut, hlslFileName, entryPoint, shaderModel, pBlob.ReleaseAndGetAddressOf()));
	HR(Graphics::GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
}

void PixelShader::Bind() const
{
	Graphics::GetContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
