#pragma once

#include <DirectXMath.h>

class Collision
{
public:

	/*static bool IntersectSphereVsSphere(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		const DirectX::XMFLOAT3& positionB,
		DirectX::XMFLOAT3& outPositionB
	);*/
	bool IntersectSphereVsSphere(
		const DirectX::XMFLOAT3& positionA, 
		float radiusA, 
		float heightA, 
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		float heightB,
		DirectX::XMFLOAT3& outPositionB);

	static bool IntersectCylinderVsCylinder(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		float heightA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		float heightB,
		DirectX::XMFLOAT3& outPositionB);
};

