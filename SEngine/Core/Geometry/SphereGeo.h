#pragma once
#include "GeometryBase.h"
#include "..\Vertex\Vertex.h"
#include <DirectXMath.h>

// 球生成参考了X_Jun第7章
class SpherePosColGeo : public GeometryBase<VertexPosColor>
{
public:
    SpherePosColGeo(float radius, UINT levels, UINT slices, const DirectX::XMFLOAT4& color)
	{
        UINT vertexCount = 2 + (levels - 1) * (slices + 1);
        UINT indexCount = 6 * (levels - 1) * slices;
        vertices.resize(vertexCount);
        indices.resize(indexCount);

        VertexPosColor vertexData(DirectX::XMFLOAT3(0.0f, radius, 0.0f), color);
        unsigned short vIndex = 0, iIndex = 0;

        float phi = 0.0f, theta = 0.0f;
        float per_phi = DirectX::XM_PI / levels;
        float per_theta = DirectX::XM_2PI / slices;
        float x, y, z;

        // 放入顶端点
        vertices[vIndex++] = vertexData;

        for (UINT i = 1; i < levels; ++i)
        {
            phi = per_phi * i;
            // 需要slices + 1个顶点是因为 起点和终点需为同一点，但纹理坐标值不一致
            for (UINT j = 0; j <= slices; ++j)
            {
                theta = per_theta * j;
                x = radius * sinf(phi) * cosf(theta);
                y = radius * cosf(phi);
                z = radius * sinf(phi) * sinf(theta);
                // 计算出局部坐标
                DirectX::XMFLOAT3 pos = DirectX::XMFLOAT3(x, y, z);

                vertexData = { pos, color };
                vertices[vIndex++] = vertexData;
            }
        }

        // 放入底端点
        vertexData = { DirectX::XMFLOAT3(0.0f, -radius, 0.0f),  color };
        vertices[vIndex++] = vertexData;

        // 逐渐放入索引
        if (levels > 1)
        {
            for (UINT j = 1; j <= slices; ++j)
            {
                indices[iIndex++] = 0;
                indices[iIndex++] = j % (slices + 1) + 1;
                indices[iIndex++] = j;
            }
        }


        for (UINT i = 1; i < levels - 1; ++i)
        {
            for (UINT j = 1; j <= slices; ++j)
            {
                indices[iIndex++] = (i - 1) * (slices + 1) + j;
                indices[iIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
                indices[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;

                indices[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
                indices[iIndex++] = i * (slices + 1) + j;
                indices[iIndex++] = (i - 1) * (slices + 1) + j;
            }
        }

        // 逐渐放入索引
        if (levels > 1)
        {
            for (UINT j = 1; j <= slices; ++j)
            {
                indices[iIndex++] = (levels - 2) * (slices + 1) + j;
                indices[iIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
                indices[iIndex++] = (levels - 1) * (slices + 1) + 1;
            }
        }
	}
	~SpherePosColGeo() override {};
};

class SpherePosTexGeo : public GeometryBase<VertexPosTex>
{
public:
    SpherePosTexGeo(float radius, UINT levels, UINT slices)
    {
        UINT vertexCount = 2 + (levels - 1) * (slices + 1);
        UINT indexCount = 6 * (levels - 1) * slices;
        vertices.resize(vertexCount);
        indices.resize(indexCount);

        VertexPosTex vertexData(DirectX::XMFLOAT3(0.0f, radius, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f));
        unsigned short vIndex = 0, iIndex = 0;

        float phi = 0.0f, theta = 0.0f;
        float per_phi = DirectX::XM_PI / levels;
        float per_theta = DirectX::XM_2PI / slices;
        float x, y, z;

        // 放入顶端点
        vertices[vIndex++] = vertexData;

        for (UINT i = 1; i < levels; ++i)
        {
            phi = per_phi * i;
            // 需要slices + 1个顶点是因为 起点和终点需为同一点，但纹理坐标值不一致
            for (UINT j = 0; j <= slices; ++j)
            {
                theta = per_theta * j;
                x = radius * sinf(phi) * cosf(theta);
                y = radius * cosf(phi);
                z = radius * sinf(phi) * sinf(theta);
                // 计算出局部坐标
                DirectX::XMFLOAT3 pos = DirectX::XMFLOAT3(x, y, z);

                vertexData = { pos, DirectX::XMFLOAT2(theta / DirectX::XM_2PI, phi / DirectX::XM_PI) };
                vertices[vIndex++] = vertexData;
            }
        }

        // 放入底端点
        vertexData = { DirectX::XMFLOAT3(0.0f, -radius, 0.0f),  DirectX::XMFLOAT2(0.0f, 1.0f) };
        vertices[vIndex++] = vertexData;

        // 逐渐放入索引
        if (levels > 1)
        {
            for (UINT j = 1; j <= slices; ++j)
            {
                indices[iIndex++] = 0;
                indices[iIndex++] = j % (slices + 1) + 1;
                indices[iIndex++] = j;
            }
        }


        for (UINT i = 1; i < levels - 1; ++i)
        {
            for (UINT j = 1; j <= slices; ++j)
            {
                indices[iIndex++] = (i - 1) * (slices + 1) + j;
                indices[iIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
                indices[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;

                indices[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
                indices[iIndex++] = i * (slices + 1) + j;
                indices[iIndex++] = (i - 1) * (slices + 1) + j;
            }
        }

        // 逐渐放入索引
        if (levels > 1)
        {
            for (UINT j = 1; j <= slices; ++j)
            {
                indices[iIndex++] = (levels - 2) * (slices + 1) + j;
                indices[iIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
                indices[iIndex++] = (levels - 1) * (slices + 1) + 1;
            }
        }
    }
    ~SpherePosTexGeo() override {};
};