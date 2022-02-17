#pragma once
#include "Bindable.h"
#include <vector>

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(const std::vector<unsigned short>& indices);
	void Bind() const override;
	UINT GetCount() const noexcept
	{
		return count;
	}
private:
	UINT count;
	ComPtr<ID3D11Buffer> pIndexBuffer;
};