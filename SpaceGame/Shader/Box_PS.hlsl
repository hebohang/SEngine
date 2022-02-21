#include "Base.hlsli"

struct VertexOut
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
};

// 像素着色器
float4 PS(VertexOut pIn) : SV_Target
{
    return pIn.color;
}
