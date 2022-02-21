#include "SkyBox.hlsli"

struct VertexOut
{
    float4 posH : SV_POSITION;
    float3 posL : POSITION;
};

float4 PS(VertexOut pIn) : SV_Target
{
    return g_TexCube.Sample(g_Sam, pIn.posL);
}