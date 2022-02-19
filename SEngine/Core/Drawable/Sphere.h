#pragma once
#include "Drawable.h"
#include "..\Component\Transform.h"

class Sphere : public Drawable
{
public:
	Sphere(float radius = 1.0f, UINT levels = 20, UINT slices = 20, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
public:
	Transform trans;
};