#pragma once
#include "System/ModelRenderer.h"
#include "Character.h"
#include "ProjectileManager.h"

class Player : public Character
{
public:
	Player();
		~Player()override;
	void DrawDebugGUI();
	void Update(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer);

	/*void Jump(float speed);
	void UpdateVelocity(float elapsedTime);*/
	void InputJump();

	//	debugプリミーテァブ
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer) override;

private:
		DirectX::XMFLOAT3 GetMoveVec()const;

		/*void Move(float elapsedTime, float vx, float vz, float speed);*/

		void InputMove(float elapsedTime);

		/*void Turn(float elapsedTime, float vx, float vz, float speed);*/

		void CollisionPlayerVsEnemies();

		void InputProjectile();
protected:

	void OnLanding() override;

private:
	Model* model = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
	
	//06
	float jumpSpeed = 12.0f;
	/*float gravity = -30.0f;
	DirectX::XMFLOAT3 velocity = { 0,0,0 };*/
	int jumpCount = 0;
	int jumpLimit = 2;
	ProjectileManager projectileManager;
};