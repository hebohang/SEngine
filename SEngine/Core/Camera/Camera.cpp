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

void Camera::Update() const
{
	pCameraCbuffer->Update({ XMMatrixTranspose(Camera::GetViewXM()) , XMMatrixTranspose(Camera::GetProjXM()) });
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


void FirstPersonCamera::Strafe(float d)
{
	trans.Translate(trans.GetRightAxis(), d);
}

void FirstPersonCamera::Walk(float d)
{
	XMVECTOR rightVec = trans.GetRightAxisXM();
	XMVECTOR frontVec = XMVector3Normalize(XMVector3Cross(rightVec, g_XMIdentityR1));
	XMFLOAT3 front;
	XMStoreFloat3(&front, frontVec);
	trans.Translate(front, d);
}

void FirstPersonCamera::MoveForward(float d)
{
	trans.Translate(trans.GetForwardAxis(), d);
}

void FirstPersonCamera::Pitch(float rad)
{
	XMFLOAT3 rotation = trans.GetRotation();
	// 将绕x轴旋转弧度限制在[-7pi/18, 7pi/18]之间
	rotation.x += rad;
	if (rotation.x > XM_PI * 7 / 18)
		rotation.x = XM_PI * 7 / 18;
	else if (rotation.x < -XM_PI * 7 / 18)
		rotation.x = -XM_PI * 7 / 18;

	trans.SetRotation(rotation);
}

void FirstPersonCamera::RotateY(float rad)
{
	XMFLOAT3 rotation = trans.GetRotation();
	rotation.y = XMScalarModAngle(rotation.y + rad);
	trans.SetRotation(rotation);
}