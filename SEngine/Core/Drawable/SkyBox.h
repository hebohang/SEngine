#pragma once
#include "Drawable.h"

class SkyBox : public Drawable
{
public:
	SkyBox(const std::vector<std::wstring>& CubMapPath);
	SkyBox(const std::wstring& CubMapPath);  // DDS 版本
};