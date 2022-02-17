#include "VertexBuffer.h"

void VertexBuffer::Bind() const 
{
	const UINT offset = 0u;
	Graphics::GetContext()->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}