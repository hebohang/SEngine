#pragma once
#include "Bindable.h"
#include <vector>

class Texture : public Bindable
{
public:
	Texture(const wchar_t* TexPath);  // 单张纹理
	Texture(const std::vector<std::wstring>& CubMapPath);  // 天空盒纹理
	void Bind() const override;
	void BindToSlot(UINT slot) const;
private:
	ComPtr<ID3D11ShaderResourceView> pTexture;
	// 一次可能绑定多张纹理
	// std::vector<ComPtr<ID3D11ShaderResourceView>> mTextures;
};