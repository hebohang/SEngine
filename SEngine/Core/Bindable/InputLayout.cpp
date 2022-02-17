#include "InputLayout.h"
#include "..\ErrorHandle\DXTrace.h"

template<typename VertexType>
InputLayout<VertexType>::InputLayout(Graphics& gfx, VertexType& vertex, ID3DBlob* pVsBlob)
	:
	pInputLayout(nullptr)
{
	Graphics::GetDevice()->CreateInputLayout(
		vertex.GetInputElementDesc(), 
		vertex.GetInputElementSize(),
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
