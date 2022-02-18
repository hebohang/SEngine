#include "TransformCBuffer.h"

TransformCBuffer::TransformCBuffer(Transform& _TransData)
	:
	VertexConstantBuffer<DirectX::XMMATRIX>(_TransData.GetModelMatrix()),
	TransData(_TransData)
{}

void TransformCBuffer::Update() const
{
	// 记得 C++ 端默认行主序矩阵，HLSL 端默认列主序！所以这里要转置！摄像机的 view 和 proj 同理！
	ConstantBuffer<DirectX::XMMATRIX>::Update(XMMatrixTranspose(TransData.GetModelMatrix()));
}

void TransformCBuffer::Bind() const
{
	Update();
	Graphics::GetContext()->VSSetConstantBuffers(0u, 1u, pConstantBufferGPU.GetAddressOf());
}


	