#pragma once
#include "..\Bindable\Bindable.h"
#include <vector>
#include <DirectXMath.h>

template<typename VertexType>
class GeometryBase
{
public:
	GeometryBase() = default;
	GeometryBase(std::vector<VertexType> _vertices, std::vector<unsigned short> _indices)
		:
		vertices(std::move(_vertices)),
		indices(std::move(_indices))
	{}
	virtual ~GeometryBase() = 0;
public:
	void Transform(DirectX::FXMMATRIX matrix);
public:
	std::vector<VertexType> vertices;
	std::vector<unsigned short> indices;
};

template<typename VertexType>
inline GeometryBase<VertexType>::~GeometryBase() {}

template<typename VertexType>
inline void GeometryBase<VertexType>::Transform(DirectX::FXMMATRIX matrix)
{
	for (auto& v : vertices)
	{
		const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&v.pos);
		DirectX::XMStoreFloat3(
			&v.pos,
			DirectX::XMVector3Transform(pos, matrix)
		);
	}
}