#include "SkyBox.hlsli"

struct VertexIn
{
    float3 posL : POSITION;
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float3 posL : POSITION;
};

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    
    // 设置z = w使得z/w = 1(天空盒保持在远平面)
    float4 posH = mul(float4(vIn.posL, 1.0f), g_World);
    posH = mul(posH, g_View);
    posH = mul(posH, g_Proj);
    vOut.posH = posH.xyww;
    vOut.posL = vIn.posL;
    return vOut;
}