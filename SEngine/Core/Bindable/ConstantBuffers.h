#pragma once
#include "Bindable.h"
#include "DXTrace.h"

template<typename CbType>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(const CbType& Cb)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;  // 常量缓冲区我们默认 DYNAMIC，即CPU端可做更改
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(Cb);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &Cb;
		HR(Graphics::GetDevice()->CreateBuffer(&cbd, &csd, &pConstantBufferGPU));
	}
	
protected:
	ComPtr<ID3D11Buffer> pConstantBufferGPU;
	// CPU端的Buffer对应，每次用可用 Map 方法更改
	CbType mConstantBufferCPU;
};