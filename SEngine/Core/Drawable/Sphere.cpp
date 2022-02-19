#include "Sphere.h"
#include "..\Geometry\SphereGeo.h"
#include "..\Bindable\BindableBase.h"
#include "..\Vertex\Vertex.h"
#include "..\Bindable\TransformCBuffer.h"
#include <DirectXMath.h>

Sphere::Sphere(float radius, UINT levels, UINT slices, const DirectX::XMFLOAT4& color)
{
	SphereGeo sphere(radius, levels, slices, color);
	BindGeometry(sphere);

	auto pVS = std::make_unique<VertexShader>(L"..\\SEngine\\Shader\\Cube_VS.cso", L"..\\SEngine\\Shader\\Cube_VS.hlsl");
	auto pVSBlob = pVS->GetBlob();
	AddBind(std::move(pVS));
	AddBind(std::make_unique<InputLayout>(sphere.vertices[0].GetInputElementVec(), pVSBlob));

	AddBind(std::make_unique<PixelShader>(L"..\\SEngine\\Shader\\Cube_PS.cso", L"..\\SEngine\\Shader\\Cube_PS.hlsl"));

	AddBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCBuffer>(trans));
}