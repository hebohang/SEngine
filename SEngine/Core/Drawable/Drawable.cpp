#include "Drawable.h"
#include "..\Bindable\IndexBuffer.h"

void Drawable::Draw() const
{
	UINT DrawCount = 0;
	for (const auto& b : binds)
	{
		if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
		{
			DrawCount = p->GetCount();
		}
		b->Bind();
	}
	Graphics::GetContext()->DrawIndexed(DrawCount, 0u, 0u);
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind)
{
	binds.emplace_back(std::move(bind));
}
