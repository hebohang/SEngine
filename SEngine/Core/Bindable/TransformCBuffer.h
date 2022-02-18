#pragma once
#include "ConstantBuffers.h"
#include "..\Component\Transform.h"
#include <DirectXMath.h>

class TransformCBuffer : public VertexConstantBuffer<DirectX::XMMATRIX>
{
public:
	TransformCBuffer() = default;
	TransformCBuffer(const Transform& _TransData);
	void Update();
public:
	Transform TransData;
};