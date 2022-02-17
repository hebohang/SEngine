#include "InputLayout.h"
#include "..\ErrorHandle\DXTrace.h"

InputLayout::InputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVsBlob)
	:
	pInputLayout(nullptr)
{
	Graphics::GetDevice()->CreateInputLayout(
		layout.data(),
		(UINT)layout.size(),
		pVsBlob->GetBufferPointer(),
		pVsBlob->GetBufferSize(),
		&pInputLayout
	);
}

void InputLayout::Bind() const
{
	Graphics::GetContext()->IASetInputLayout(pInputLayout.Get());
}
