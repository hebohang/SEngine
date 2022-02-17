#include "VertexShader.h"
#include "..\ErrorHandle\DXTrace.h"
#include "..\Common\d3dUtil.h"

VertexShader::VertexShader(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName, LPCSTR entryPoint, LPCSTR shaderModel)
	:
	pBlob(nullptr),
	pVertexShader(nullptr)
{
	HR(CreateShaderFromFile(csoFileNameInOut, hlslFileName, entryPoint, shaderModel, pBlob.ReleaseAndGetAddressOf()));
	HR(Graphics::GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));
}

void VertexShader::Bind() const
{
	Graphics::GetContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}
