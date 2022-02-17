#pragma once
#include "Bindable.h"
#include "..\Vertex\Vertex.h"

template<typename VertexType>
class InputLayout : public Bindable
{
public:
	InputLayout(ID3DBlob* pVsBlob);
	void Bind() const override;
private:
	ComPtr<ID3D11InputLayout> pInputLayout;
};