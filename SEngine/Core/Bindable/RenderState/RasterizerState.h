#pragma once
#include "..\Bindable.h"

enum class RasterizerStateType
{
	NoCull = 0,
	BackCull = 1,
};

class RasterizerState : public Bindable
{
public:
	RasterizerState(RasterizerStateType Type);
	void Bind() const override;
private:
	RasterizerStateType Type;
	static ComPtr<ID3D11RasterizerState> pRasterizerStateNoCull; 
	static ComPtr<ID3D11RasterizerState> pRasterizerStateBackCull; // 默认 Bind 
};