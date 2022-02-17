#pragma once
#include "Bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName,
		LPCSTR entryPoint = "PS", LPCSTR shaderModel = "ps_5_0");
	void Bind() const override;
private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};