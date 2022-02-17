#pragma once
#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName, 
		LPCSTR entryPoint = "VS", LPCSTR shaderModel = "vs_5_0");
	void Bind() const override;

	// 主要给创建 InputLayout 用
	ID3DBlob* GetBlob() const noexcept
	{
		return pBlob.Get();
	}
private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};