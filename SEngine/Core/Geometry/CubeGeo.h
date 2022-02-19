#pragma once
#include "GeometryBase.h"
#include "..\Vertex\Vertex.h"
#include <DirectXMath.h>

class CubeGeo : public GeometryBase<VertexPosColor>
{
public:
	CubeGeo()
	{
		vertices =
		{
			{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f),  DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f),   DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f),  DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f),  DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),   DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),    DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f),   DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) }
		};

		indices = {
			// 正面
			0, 1, 2,
			2, 3, 0,
			// 左面
			4, 5, 1,
			1, 0, 4,
			// 顶面
			1, 5, 6,
			6, 2, 1,
			// 背面
			7, 6, 5,
			5, 4, 7,
			// 右面
			3, 2, 6,
			6, 7, 3,
			// 底面
			4, 0, 3,
			3, 7, 4
		};
	}
	~CubeGeo() override {}
};