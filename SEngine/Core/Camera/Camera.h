#pragma once

#include <d3d11_1.h>
#include <DirectXMath.h>
#include "..\Component\Transform.h"
#include "..\Bindable\ConstantBuffers.h"

class Camera
{
public:
	struct CameraConstantBuffer
	{
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX proj;
	};
public:
	Camera() = default;
	virtual ~Camera() {};
public:
	//
	// 获取矩阵
	//
	DirectX::XMMATRIX GetViewXM() const;
	DirectX::XMMATRIX GetProjXM() const;
public:
	void ActiveCamera();
protected:
	Transform trans;

	// 视锥体属性
	float mNearZ = 1.0f;
	float mFarZ = 1000.0f;
	float mFovY = DirectX::XM_PI / 3;

	std::unique_ptr<VertexConstantBuffer<CameraConstantBuffer>> pCameraCbuffer;
};

class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera() = default;
	~FirstPersonCamera();

	// 设置摄像机位置
	void SetPosition(float x, float y, float z);
	void SetPosition(const DirectX::XMFLOAT3& pos);
	// 设置摄像机的朝向
	void LookAt(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& up = { 0.0f, 1.0f, 0.0f });
	void LookTo(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& to, const DirectX::XMFLOAT3& up = { 0.0f, 1.0f, 0.0f });
};