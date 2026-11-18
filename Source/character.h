#pragma once
#include <DirectXMath.h>
#include "System/ShapeRenderer.h"

class Character
{
public:
	Character() {}
	virtual~Character() {}
	
	void UpdateTransform();
	const DirectX::XMFLOAT3& GetPosition() const { return position; }

	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

	const DirectX::XMFLOAT3& GetAngle()const { return angle; }

	void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }

	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }

	float GetRadius() const { return radius; }

	virtual void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	bool IsGround() const {return isGround;}

	float GetHeight() const { return height; }
protected:

	void Move(float elapsedTime, float vx, float vz, float speed);
	void InputMove(float elapsedTime);
	void Turn(float elapsedTime, float vx, float vz, float speed);
	void Jump(float speed);
	void UpdateVelocity(float elapsedTime);
	virtual void OnLanding() {}
	float height = 2.0f;

protected:

	DirectX::XMFLOAT3   position = { 0,0,0 };
	DirectX::XMFLOAT3   angle = { 0,0,0 };
	DirectX::XMFLOAT3   scale = { 1,1,1 };
	DirectX::XMFLOAT4X4  transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};

	float radius = 0.5f;

	float gravity = -30.0f;
	DirectX::XMFLOAT3 velocity = { 0,0,0 };

	bool isGround = false;
};