#pragma once
#include "..\Bindable.h"

enum class SamplerStateType
{
	LinearWrap = 0,
	AnisotropicWrap = 1,
};

class SamplerState : public Bindable
{
public:
	SamplerState();
	void Bind() const override;
	void BindWithType(SamplerStateType Type) const;
private:
	static ComPtr<ID3D11SamplerState> pSamplerStateLinear; // 默认 Bind 为 Linear 的
	static ComPtr<ID3D11SamplerState> pSamplerStateAnisotropic; 
};