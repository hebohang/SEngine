#include "SkyBox.h"
#include "..\Vertex\Vertex.h"
#include "..\Geometry\SphereGeo.h"
#include "..\Bindable\BindableBase.h"

SkyBox::SkyBox(const std::vector<std::wstring>& CubMapPath)
{
	assert(CubMapPath.size() && "纹理数组为空");

	SpherePosGeo sphere(5000.0f);
	BindGeometry(sphere);

	AddBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<Texture>(CubMapPath));
	AddBind(std::make_unique<SamplerState>());
	AddBind(std::make_unique<RasterizerState>(RasterizerStateType::NoCull));
	AddBind(std::make_unique<DepthStencilState>(DepthStencilStateType::LessEqual));

	auto pVS = std::make_unique<VertexShader>(L"..\\SEngine\\Shader\\SkyBox_VS.cso", L"..\\SEngine\\Shader\\SkyBox_VS.hlsl");
	auto pVSBlob = pVS->GetBlob();
	AddBind(std::move(pVS));
	AddBind(std::make_unique<InputLayout>(sphere.vertices[0].GetInputElementVec(), pVSBlob));

	AddBind(std::make_unique<PixelShader>(L"..\\SEngine\\Shader\\SkyBox_PS.cso", L"..\\SEngine\\Shader\\SkyBox_PS.hlsl"));
}

SkyBox::SkyBox(const std::wstring& CubMapPath)
{
	assert(CubMapPath.size() && "纹理为空");

	SpherePosGeo sphere(5000.0f);
	BindGeometry(sphere);

	AddBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<Texture>(CubMapPath));
	AddBind(std::make_unique<SamplerState>());
	AddBind(std::make_unique<RasterizerState>(RasterizerStateType::NoCull));
	AddBind(std::make_unique<DepthStencilState>(DepthStencilStateType::LessEqual));

	auto pVS = std::make_unique<VertexShader>(L"..\\SEngine\\Shader\\SkyBox_VS.cso", L"..\\SEngine\\Shader\\SkyBox_VS.hlsl");
	auto pVSBlob = pVS->GetBlob();
	AddBind(std::move(pVS));
	AddBind(std::make_unique<InputLayout>(sphere.vertices[0].GetInputElementVec(), pVSBlob));

	AddBind(std::make_unique<PixelShader>(L"..\\SEngine\\Shader\\SkyBox_PS.cso", L"..\\SEngine\\Shader\\SkyBox_PS.hlsl"));
}
