#include "Transform.h"

using namespace DirectX;

Transform::Transform(const DirectX::XMFLOAT3& scale, const DirectX::XMFLOAT3& rotation, const DirectX::XMFLOAT3& position)
	: mScale(scale), mRotation(rotation), mPosition(position)
{
}

XMFLOAT3 Transform::GetScale() const
{
	return mScale;
}

DirectX::XMVECTOR Transform::GetScaleXM() const
{
	return XMLoadFloat3(&mScale);
}

XMFLOAT3 Transform::GetRotation() const
{
	return mRotation;
}

DirectX::XMVECTOR Transform::GetRotationXM() const
{
	return XMLoadFloat3(&mRotation);
}

XMFLOAT3 Transform::GetPosition() const
{
	return mPosition;
}

DirectX::XMVECTOR Transform::GetPositionXM() const
{
	return XMLoadFloat3(&mPosition);
}

XMFLOAT3 Transform::GetRightAxis() const
{
	XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&mRotation));
	XMFLOAT3 right;
	XMStoreFloat3(&right, R.r[0]);
	return right;
}

DirectX::XMVECTOR Transform::GetRightAxisXM() const
{
	XMFLOAT3 right = GetRightAxis();
	return XMLoadFloat3(&right);
}

XMFLOAT3 Transform::GetUpAxis() const
{
	XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&mRotation));
	XMFLOAT3 up;
	XMStoreFloat3(&up, R.r[1]);
	return up;
}

DirectX::XMVECTOR Transform::GetUpAxisXM() const
{
	XMFLOAT3 up = GetUpAxis();
	return XMLoadFloat3(&up);
}

XMFLOAT3 Transform::GetForwardAxis() const
{
	XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&mRotation));
	XMFLOAT3 forward;
	XMStoreFloat3(&forward, R.r[2]);
	return forward;
}

DirectX::XMVECTOR Transform::GetForwardAxisXM() const
{
	XMFLOAT3 forward = GetForwardAxis();
	return XMLoadFloat3(&forward);
}

XMMATRIX Transform::GetModelMatrix() const
{
	XMVECTOR scaleVec = XMLoadFloat3(&mScale);
	XMVECTOR rotationVec = XMLoadFloat3(&mRotation);
	XMVECTOR positionVec = XMLoadFloat3(&mPosition);
	XMMATRIX World = XMMatrixScalingFromVector(scaleVec) * XMMatrixRotationRollPitchYawFromVector(rotationVec) * XMMatrixTranslationFromVector(positionVec);
	return World;
}

DirectX::XMMATRIX Transform::GetModelInverseMatrix() const
{
	XMMATRIX InvWorld = XMMatrixInverse(nullptr, GetModelMatrix());
	return InvWorld;
}


void Transform::SetScale(const XMFLOAT3& scale)
{
	mScale = scale;
}

void Transform::SetScale(float x, float y, float z)
{
	mScale = XMFLOAT3(x, y, z);
}

void Transform::SetRotation(const XMFLOAT3& eulerAnglesInRadian)
{
	mRotation = eulerAnglesInRadian;
}

void Transform::SetRotation(float x, float y, float z)
{
	mRotation = XMFLOAT3(x, y, z);
}

void Transform::SetPosition(const XMFLOAT3& position)
{
	mPosition = position;
}

void Transform::SetPosition(float x, float y, float z)
{
	mPosition = XMFLOAT3(x, y, z);
}

void Transform::Rotate(const XMFLOAT3& eulerAnglesInRadian)
{
	XMVECTOR newRotationVec = XMVectorAdd(XMLoadFloat3(&mRotation), XMLoadFloat3(&eulerAnglesInRadian));
	XMStoreFloat3(&mRotation, newRotationVec);
}

void Transform::RotateAxis(const XMFLOAT3& axis, float radian)
{
	XMVECTOR rotationVec = XMLoadFloat3(&mRotation);
	XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(rotationVec) *
		XMMatrixRotationAxis(XMLoadFloat3(&axis), radian);
	XMFLOAT4X4 rotMatrix;
	XMStoreFloat4x4(&rotMatrix, R);
	mRotation = GetEulerAnglesFromRotationMatrix(rotMatrix);
}

void Transform::RotateAround(const XMFLOAT3& point, const XMFLOAT3& axis, float radian)
{
	XMVECTOR rotationVec = XMLoadFloat3(&mRotation);
	XMVECTOR positionVec = XMLoadFloat3(&mPosition);
	XMVECTOR centerVec = XMLoadFloat3(&point);

	// ???point????????????????????????
	XMMATRIX RT = XMMatrixRotationRollPitchYawFromVector(rotationVec) * XMMatrixTranslationFromVector(positionVec - centerVec);
	RT *= XMMatrixRotationAxis(XMLoadFloat3(&axis), radian);
	RT *= XMMatrixTranslationFromVector(centerVec);
	XMFLOAT4X4 rotMatrix;
	XMStoreFloat4x4(&rotMatrix, RT);
	mRotation = GetEulerAnglesFromRotationMatrix(rotMatrix);
	XMStoreFloat3(&mPosition, RT.r[3]);
}

void Transform::Translate(const XMFLOAT3& direction, float magnitude)
{
	XMVECTOR directionVec = XMVector3Normalize(XMLoadFloat3(&direction));
	XMVECTOR newPosition = XMVectorMultiplyAdd(XMVectorReplicate(magnitude), directionVec, XMLoadFloat3(&mPosition));
	XMStoreFloat3(&mPosition, newPosition);
}

void Transform::LookAt(const XMFLOAT3& target, const XMFLOAT3& up)
{
	XMMATRIX View = XMMatrixLookAtLH(XMLoadFloat3(&mPosition), XMLoadFloat3(&target), XMLoadFloat3(&up));
	XMMATRIX InvView = XMMatrixInverse(nullptr, View);
	XMFLOAT4X4 rotMatrix;
	XMStoreFloat4x4(&rotMatrix, InvView);
	mRotation = GetEulerAnglesFromRotationMatrix(rotMatrix);
}

void Transform::LookTo(const XMFLOAT3& direction, const XMFLOAT3& up)
{
	XMMATRIX View = XMMatrixLookToLH(XMLoadFloat3(&mPosition), XMLoadFloat3(&direction), XMLoadFloat3(&up));
	XMMATRIX InvView = XMMatrixInverse(nullptr, View);
	XMFLOAT4X4 rotMatrix;
	XMStoreFloat4x4(&rotMatrix, InvView);
	mRotation = GetEulerAnglesFromRotationMatrix(rotMatrix);
}

XMFLOAT3 Transform::GetEulerAnglesFromRotationMatrix(const XMFLOAT4X4& rotationMatrix)
{
	// ?????????????????????????????????
	float c = sqrtf(1.0f - rotationMatrix(2, 1) * rotationMatrix(2, 1));
	// ??????r[2][1]????????????1?????????
	if (isnan(c))
		c = 0.0f;
	XMFLOAT3 rotation;
	rotation.z = atan2f(rotationMatrix(0, 1), rotationMatrix(1, 1));
	rotation.x = atan2f(-rotationMatrix(2, 1), c);
	rotation.y = atan2f(rotationMatrix(2, 0), rotationMatrix(2, 2));
	return rotation;
}