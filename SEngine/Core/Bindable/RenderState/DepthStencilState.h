#pragma once
#include "..\Bindable.h"

enum class DepthStencilStateType
{
	LessEqual = 0,
	NoDepthWriteWithStencil = 1,
};

class DepthStencilState : public Bindable
{
public:
	DepthStencilState(DepthStencilStateType Type);
	void Bind() const override;
private:
	DepthStencilStateType Type;
	static ComPtr<ID3D11DepthStencilState> pDepthStencilStateLessEqual;
	static ComPtr<ID3D11DepthStencilState> pDepthStencilStateNoDepthWriteWithStencil;
};