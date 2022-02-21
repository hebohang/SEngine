#include "Base.hlsli"

struct VertexOut
{
    float4 posH : SV_POSITION;
    float2 Tex : TEXCOORD;
};

// 像素着色器
float4 PS(VertexOut pIn) : SV_Target
{
    return g_Tex.Sample(g_SamLinear, pIn.Tex);
}
