#pragma once
#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName, 
		LPCSTR entryPoint = "VS", LPCSTR shaderModel = "vs_5_0");
	void Bind() const override;
private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};