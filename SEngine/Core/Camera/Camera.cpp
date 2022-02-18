#include "Camera.h"
#include "..\Common\d3dApp.h"
#include <memory>
using namespace DirectX;

DirectX::XMMATRIX Camera::GetViewXM() const
{
	return trans.GetModelInverseMatrix();
}

DirectX::XMMATRIX Camera::GetProjXM() const
{
	return XMMatrixPerspectiveFovLH(mFovY, D3DApp::GetAspectRatio(), mNearZ, mFarZ);
}

void Camera::ActiveCamera()
{
	CameraConstantBuffer ccb = { XMMatrixTranspose(Camera::GetViewXM()) , XMMatrixTranspose(Camera::GetProjXM()) };
	pCameraCbuffer = std::make_unique<VertexConstantBuffer<CameraConstantBuffer>>(ccb);
	pCameraCbuffer->BindToSlot(1u);
}

// ******************
// 第一人称/自由视角摄像机
//

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

void FirstPersonCamera::SetPosition(const XMFLOAT3& pos)
{
	trans.SetPosition(pos);
}

void FirstPersonCamera::LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up)
{
	trans.SetPosition(pos);
	trans.LookAt(target, up);
}

void FirstPersonCamera::LookTo(const XMFLOAT3& pos, const XMFLOAT3& to, const XMFLOAT3& up)
{
	trans.SetPosition(pos);
	trans.LookTo(to, up);
}