#pragma once
#include "ConstantBuffers.h"
#include "..\Component\Transform.h"
#include <DirectXMath.h>

class TransformCBuffer : public VertexConstantBuffer<DirectX::XMMATRIX>
{
public:
	TransformCBuffer() = default;
	TransformCBuffer(Transform& _TransData);
	void Update() const;
	void Bind() const override;
public:
	Transform& TransData;
};