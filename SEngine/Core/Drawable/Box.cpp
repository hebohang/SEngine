#include "Box.h"
#include "..\Vertex\Vertex.h"
#include "..\Geometry\CubeGeo.h"
#include "..\Bindable\BindableBase.h"
#include <DirectXMath.h>

Box::Box()
{
	CubeGeo cube;
	BindGeometry(cube);

	auto pVS = std::make_unique<VertexShader>(L"..\\SEngine\\Shader\\Box_VS.cso", L"..\\SEngine\\Shader\\Box_VS.hlsl");
	auto pVSBlob = pVS->GetBlob();
	AddBind(std::move(pVS));
	AddBind(std::make_unique<InputLayout>(cube.vertices[0].GetInputElementVec(), pVSBlob));

	AddBind(std::make_unique<PixelShader>(L"..\\SEngine\\Shader\\Box_PS.cso", L"..\\SEngine\\Shader\\Box_PS.hlsl"));

	AddBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCBuffer>(trans));

	AddBind(std::make_unique<RasterizerState>(RasterizerStateType::BackCull));
}