#pragma once
#include "Bindable.h"
#include <vector>

class Texture : public Bindable
{
public:
	Texture(const wchar_t* TexPath);
	void Bind() const override;
	void BindToSlot(UINT slot) const;
private:
	ComPtr<ID3D11ShaderResourceView> pTexture;
	// 一次可能绑定多张纹理
	// std::vector<ComPtr<ID3D11ShaderResourceView>> mTextures;
};