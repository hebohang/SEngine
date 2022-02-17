#pragma once
#include "Bindable.h"
#include "..\Vertex\Vertex.h"

class InputLayout : public Bindable
{
public:
	InputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVsBlob);
	void Bind() const override;
private:
	ComPtr<ID3D11InputLayout> pInputLayout;
};