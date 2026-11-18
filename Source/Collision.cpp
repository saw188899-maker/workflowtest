#include "Collision.h"

//bool Collision::IntersectSphereVsSphere(
//    const DirectX::XMFLOAT3& positionA,
//    float radiusA,
//    float heightA,
//    const DirectX::XMFLOAT3& positionB,
//    float radiusB,
//    float heightB,
//    DirectX::XMFLOAT3& outPositionB)

 bool Collision::IntersectCylinderVsCylinder(
    const DirectX::XMFLOAT3& positionA,
    float radiusA,
    float heightA,
    const DirectX::XMFLOAT3& positionB,
    float radiusB,
    float heightB,
	  DirectX::XMFLOAT3& outPositionB)

{
    // Aの足元がBの頭より上なら当たっていない
    if (positionA.y > positionB.y + heightB)
    {
        return false;
    }

    // Aの頭がBの足元より下なら当たっていない
    if (positionA.y + heightA < positionB.y)
    {
        return false;
    }

    // XZ平面での範囲チェック
    float vx = positionA.x - positionB.x;
    float vz = positionA.z - positionB.z;
    float range = radiusA + radiusB;
    float distXZ = sqrtf(vx * vx + vz * vz);

    if (distXZ > range)
    {
        return false;
    }

    // 単位ベクトル化
    if (distXZ > 0.0f)
    {
        vx /= distXZ;
        vz /= distXZ;
    }
    else
    {
        vx = 1.0f;
        vz = 0.0f;
    }

    // AがBを押し出す
    outPositionB.x = positionA.x - vx * range;
    outPositionB.y = positionB.y;
    outPositionB.z = positionA.z - vz * range;

    return true;
}

//{
//
//	DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
//	DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
//	DirectX::XMVECTOR Vec       = DirectX::XMVectorSubtract(PositionB, PositionA);
//	DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
//	float lengthSq;
//	DirectX::XMStoreFloat(&lengthSq, LengthSq);
//
//	float range = radiusA + radiusB;
//	if (lengthSq > range * range)
//		{
//
//			return false;
//		}
//	Vec =DirectX::XMVector3Normalize(Vec);
//	Vec =DirectX::XMVectorScale(Vec,range);
//	PositionB = DirectX::XMVectorAdd(PositionA, Vec);
//	DirectX::XMStoreFloat3(&outPositionB,PositionB );
//
//
//
//	return true;
//}