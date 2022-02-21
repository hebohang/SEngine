cbuffer ConstantBuffer : register(b0)
{
    matrix g_World;
}

cbuffer CameraConstantBuffer : register(b1)
{
    matrix g_View;
    matrix g_Proj;
}
