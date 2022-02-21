#pragma once
#include "Bindable.h"

class SamplerState : public Bindable
{
public:
	SamplerState();
	void Bind() const override;
private:
	ComPtr<ID3D11SamplerState> pSamplerState;
};