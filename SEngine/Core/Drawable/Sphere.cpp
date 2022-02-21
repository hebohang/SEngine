#include "Sphere.h"
#include "..\Vertex\Vertex.h"
#include "..\Geometry\SphereGeo.h"
#include "..\Bindable\BindableBase.h"
#include <DirectXMath.h>

Sphere::Sphere(float radius, UINT levels, UINT slices, const DirectX::XMFLOAT4& color, const wchar_t* TexPath)
{
	SphereGeo sphere(radius, levels, slices, color);
	BindGeometry(sphere);

	AddBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCBuffer>(trans));
	
	if (TexPath)  // 如果是带贴图版本的
	{
		AddBind(std::make_unique<Texture>(TexPath));
		AddBind(std::make_unique<SamplerState>());

		auto pVS = std::make_unique<VertexShader>(L"..\\SEngine\\Shader\\SphereTex_VS.cso", L"..\\SEngine\\Shader\\SphereTex_VS.hlsl");
		auto pVSBlob = pVS->GetBlob();
		AddBind(std::move(pVS));
		AddBind(std::make_unique<InputLayout>(sphere.vertices[0].GetInputElementVec(), pVSBlob));

		AddBind(std::make_unique<PixelShader>(L"..\\SEngine\\Shader\\SphereTex_PS.cso", L"..\\SEngine\\Shader\\SphereTex_PS.hlsl"));
	}
	else
	{
		auto pVS = std::make_unique<VertexShader>(L"..\\SEngine\\Shader\\SphereCol_VS.cso", L"..\\SEngine\\Shader\\SphereCol_VS.hlsl");
		auto pVSBlob = pVS->GetBlob();
		AddBind(std::move(pVS));
		AddBind(std::make_unique<InputLayout>(sphere.vertices[0].GetInputElementVec(), pVSBlob));

		AddBind(std::make_unique<PixelShader>(L"..\\SEngine\\Shader\\SphereCol_PS.cso", L"..\\SEngine\\Shader\\SphereCol_PS.hlsl"));
	}
}