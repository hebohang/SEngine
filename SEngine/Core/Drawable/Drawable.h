#pragma once
#include "Graphics.h"
#include <vector>
#include <memory>

class Bindable;

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	void Draw() const;
protected:
	void AddBind(std::unique_ptr<Bindable> bind);
private:
	std::vector<std::unique_ptr<Bindable>> binds;
};