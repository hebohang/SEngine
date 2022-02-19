#pragma once
#include "Graphics.h"
#include "..\Geometry\GeometryBase.h"
#include "..\Bindable\VertexBuffer.h"
#include "..\Bindable\IndexBuffer.h"
#include <vector>
#include <memory>

class Bindable;

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;
	void Draw() const;
protected:
	void AddBind(std::unique_ptr<Bindable> bind);
public:
	template<typename VertexType>
	void BindGeometry(const GeometryBase<VertexType>& geometry)
	{
		AddBind(std::make_unique<VertexBuffer>(geometry.vertices));
		AddBind(std::make_unique<IndexBuffer>(geometry.indices));
	}
private:
	std::vector<std::unique_ptr<Bindable>> binds;
};