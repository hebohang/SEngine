#pragma once

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <vector>

template<typename Derived>
struct VertexBase
{
	// 运用CRTP，需要保证子类有 std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;

	const D3D11_INPUT_ELEMENT_DESC* GetInputElementDesc() const
	{
		return static_cast<Derived*>(this)->inputLayout.data();
	}
	const UINT GetInputElementSize() const
	{
		return static_cast<Derived*>(this)->inputLayout.size();
	}
};

struct VertexPos : VertexBase<VertexPos>
{
	VertexPos(const DirectX::XMFLOAT3& _pos) : pos(_pos) {}

	DirectX::XMFLOAT3 pos;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
};

struct VertexPosColor : VertexBase<VertexPosColor>
{
	VertexPosColor(const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT4& _color) :
		pos(_pos), color(_color) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
};