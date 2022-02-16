#pragma once
#include "Graphics.h"

class Bindable
{
public:
	virtual void Bind() const = 0;
	virtual ~Bindable() = default;
protected:
	template <class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
};