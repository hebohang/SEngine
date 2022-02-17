#include "Topology.h"

Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY type)
	:
	type(type)
{
}

void Topology::Bind() const
{
	Graphics::GetContext()->IASetPrimitiveTopology(type);
}
