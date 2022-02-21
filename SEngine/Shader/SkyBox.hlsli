TextureCube g_TexCube : register(t0);
SamplerState g_Sam : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    matrix g_World;
}

cbuffer CameraConstantBuffer : register(b1)
{
    matrix g_View;
    matrix g_Proj;
}