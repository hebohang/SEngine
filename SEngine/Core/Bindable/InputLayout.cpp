#include "InputLayout.h"
#include "..\ErrorHandle\DXTrace.h"

template<typename VertexType>
InputLayout<VertexType>::InputLayout(ID3DBlob* pVsBlob)
	:
	pInputLayout(nullptr)
{
	Graphics::GetDevice()->CreateInputLayout(
		VertexType::GetInputElementDesc(),
		VertexType::GetInputElementSize(),
		pVsBlob->GetBufferPointer(),
		pVsBlob->GetBufferSize(),
		&pInputLayout
	);
}

template<typename VertexType>
void InputLayout<VertexType>::Bind() const
{
	Graphics::GetContext()->IASetInputLayout(pInputLayout.Get());
}
