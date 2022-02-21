#pragma once

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <vector>

template<typename Derived>
struct VertexBase
{
	// 运用CRTP，需要保证子类有 std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
	// 不影响类大小，我们需要用 sizeof(类名) 去确定 stride ，在 VertexBuffer 中需要

	const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetInputElementVec() const
	{
		return static_cast<const Derived*>(this)->inputLayouts;
	}
};

struct VertexPos : VertexBase<VertexPos>
{
	VertexPos(const DirectX::XMFLOAT3& _pos) : pos(_pos) {}
	VertexPos() = default;
	VertexPos(const VertexPos&) = default;

	DirectX::XMFLOAT3 pos;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
};

struct VertexPosColor : VertexBase<VertexPosColor>
{
	VertexPosColor(const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT4& _color) :
		pos(_pos), color(_color) {}
	VertexPosColor() = default;
	VertexPosColor(const VertexPosColor&) = default;

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
};

struct VertexPosTex : VertexBase<VertexPosTex>
{
	VertexPosTex(const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT2& _tex) :
		pos(_pos), tex(_tex) {}
	VertexPosTex() = default;
	VertexPosTex(const VertexPosTex&) = default;

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 tex;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
};