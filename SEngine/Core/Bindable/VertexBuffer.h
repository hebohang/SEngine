#pragma once
#include "Bindable.h"
#include "..\ErrorHandle\DXTrace.h"
#include <vector>

class VertexBuffer : public Bindable
{
public:
	template <typename VertexType>
	VertexBuffer(const std::vector<VertexType>& vertices)
		:
		stride(sizeof(VertexType))
	{
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(sizeof(VertexType) * vertices.size());
		bd.StructureByteStride = sizeof(VertexType);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();
		HR(Graphics::GetDevice()->CreateBuffer(&bd, &sd, &pVertexBuffer));
	}
	void Bind() const override;
private:
	UINT stride;
	ComPtr<ID3D11Buffer> pVertexBuffer;
};