#pragma once
#include "..\Bindable.h"

class BlendState : public Bindable
{
public:
	BlendState();
	void Bind() const override;
private:
	ComPtr<ID3D11BlendState> pSamplerState;
};