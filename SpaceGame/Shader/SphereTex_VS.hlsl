#include "Base.hlsli"

struct VertexIn
{
    float3 posL : POSITION;
    float2 Tex : TEXCOORD;
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float2 Tex : TEXCOORD;
};

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = mul(float4(vIn.posL, 1.0f), g_World);
    vOut.posH = mul(vOut.posH, g_View);
    vOut.posH = mul(vOut.posH, g_Proj);
    vOut.Tex = vIn.Tex;
    return vOut;
}
