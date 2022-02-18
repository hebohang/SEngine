#include "TransformCBuffer.h"

TransformCBuffer::TransformCBuffer(const Transform& _TransData)
	:
	VertexConstantBuffer<DirectX::XMMATRIX>(_TransData.GetModelMatrix()),
	TransData(_TransData)
{}

void TransformCBuffer::Update()
{
	ConstantBuffer<DirectX::XMMATRIX>::Update(TransData.GetModelMatrix());
}


	