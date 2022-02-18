#pragma once
#include <DirectXMath.h>

// 参考了X_JUN第32章源码设计
// 希望在 TransformCBuffer 中包含该组件，便于每次更新至常量缓冲区
// TODO：对于 Object 和 Component 的设计
class Transform
{
public:
	Transform() = default;
	Transform(const DirectX::XMFLOAT3 & scale, const DirectX::XMFLOAT3 & rotation, const DirectX::XMFLOAT3 & position);
public:
	// 我们真正要传给常量缓冲区的是这个Model矩阵
	DirectX::XMMATRIX GetModelMatrix() const;
	// 获取逆世界变换矩阵，从世界空间到局部空间，对于摄像机类来说其实就是它的 view 矩阵
	DirectX::XMMATRIX GetModelInverseMatrix() const;
public:
	// 设置对象缩放比例
	void SetScale(const DirectX::XMFLOAT3& scale);
	// 设置对象缩放比例
	void SetScale(float x, float y, float z);

	// 设置对象欧拉角(弧度制)
	// 对象将以Z-X-Y轴顺序旋转
	void SetRotation(const DirectX::XMFLOAT3& eulerAnglesInRadian);
	// 设置对象欧拉角(弧度制)
	// 对象将以Z-X-Y轴顺序旋转
	void SetRotation(float x, float y, float z);

	// 设置对象位置
	void SetPosition(const DirectX::XMFLOAT3& position);
	// 设置对象位置
	void SetPosition(float x, float y, float z);

	// 指定欧拉角旋转对象
	void Rotate(const DirectX::XMFLOAT3& eulerAnglesInRadian);
	// 指定以原点为中心绕轴旋转
	void RotateAxis(const DirectX::XMFLOAT3& axis, float radian);
	// 指定以point为旋转中心绕轴旋转
	void RotateAround(const DirectX::XMFLOAT3& point, const DirectX::XMFLOAT3& axis, float radian);

	// 沿着某一方向平移
	void Translate(const DirectX::XMFLOAT3& direction, float magnitude);
public:
	// 主要是给摄像机类使用
	// 
	// 观察某一点
	void LookAt(const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& up = { 0.0f, 1.0f, 0.0f });
	// 沿着某一方向观察
	void LookTo(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& up = { 0.0f, 1.0f, 0.0f });
private:
	// 从旋转矩阵获取旋转欧拉角
	DirectX::XMFLOAT3 GetEulerAnglesFromRotationMatrix(const DirectX::XMFLOAT4X4& rotationMatrix);
private:
	// 遵循 SRT 原则
	// 我的知乎笔记：https://zhuanlan.zhihu.com/p/413224014
	DirectX::XMFLOAT3 mScale = { 1.0f, 1.0f, 1.0f };				// 缩放
	DirectX::XMFLOAT3 mRotation = {};								// 旋转欧拉角(弧度制)
	DirectX::XMFLOAT3 mPosition = {};								// 物体中心点位置
};