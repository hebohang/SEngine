#pragma once
#include "..\Bindable.h"

enum class DepthStencilStateType
{
	LessEqual = 0,
};

class DepthStencilState : public Bindable
{
public:
	DepthStencilState();
	void Bind() const override;
private:
	static ComPtr<ID3D11DepthStencilState> pDepthStencilStateLessEqual;
};