#pragma once
#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology(D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind() const override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};