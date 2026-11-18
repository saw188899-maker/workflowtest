#include"Player.h"
#include"System/Input.h"
#include<imgui.h>
#include"Camera.h"
#include "EnemyManger.h"
#include "Collision.h"
#include "ProjectileStraight.h"

Player::Player()
{
	model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");
	scale.x = scale.y = scale.z = 0.01f;
}
Player::~Player()
{
	delete model;
}
void Player::Update(float elapsedTime)
{
	/*DirectX::XMFLOAT3 moveVec = GetMoveVec();

	float moveSpeed = this->moveSpeed * elapsedTime;
	position.x += moveVec.x * moveSpeed;
	position.z += moveVec.z * moveSpeed;*/

	InputMove(elapsedTime);

	CollisionPlayerVsEnemies();

	InputJump();
	UpdateVelocity(elapsedTime);

	// 弾丸更新処理
	projectileManager.Update(elapsedTime);

	InputProjectile();

	
	/*GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	float moveSpeed = 5.0f * elapsedTime;
	{
		position.x += ax * moveSpeed;
		position.z += ay * moveSpeed;
	}

		float rotateSpeed = DirectX::XMConvertToRadians(360) * elapsedTime;
		if (gamePad.GetButton() & GamePad::BTN_A)
		{
			angle.x += rotateSpeed;
		}
		if (gamePad.GetButton() & GamePad::BTN_B)
		{
			angle.y += rotateSpeed;
		}
		if (gamePad.GetButton() & GamePad::BTN_X)
		{
			angle.z += rotateSpeed;
		}*/
	

	UpdateTransform();
	model->UpdateTransform();
}




void Player::CollisionPlayerVsEnemies()
{
	EnemyManager& enemyManager = EnemyManager::Instance();

	int enemyCount = enemyManager.GetEnemyCount();

	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* enemy = enemyManager.GetEnemy(i);

		DirectX::XMFLOAT3 outPosition;

		if (Collision::IntersectCylinderVsCylinder(
			position,
			radius,
			height,
			enemy->GetPosition(),
			enemy->GetRadius(),
			enemy->GetHeight(),
			outPosition
		))
		{
			// 押し出し後の位置設定
			enemy->SetPosition(outPosition);
			if (velocity.y < 0.0f &&
				position.y >= enemy->GetPosition().y +
				enemy->GetHeight() * 0.5f)
			{
				Jump(jumpSpeed);
			}
		}
	}
}



void Player::InputMove(float elapsedTime)
{
	DirectX::XMFLOAT3 moveVec = GetMoveVec();

	Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed);
}




void Player::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
	projectileManager.Render(rc, renderer);

}
void Player::DrawDebugGUI()
{
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 300),ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
	{
		//Transform
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//位置(Position)
			ImGui::InputFloat3("Position", &position.x);

			//回転(Rotation)
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle.x);
			a.y = DirectX::XMConvertToDegrees(angle.y);
			a.z = DirectX::XMConvertToDegrees(angle.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x = DirectX::XMConvertToRadians(a.x);
			angle.y = DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);

			ImGui::InputFloat3("Scale", &scale.x);

		}
	}
	ImGui::End();
}
DirectX::XMFLOAT3 Player::GetMoveVec()const {

	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	Camera& camera = Camera::Instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRightX+ cameraRightZ * cameraRightZ);

	if (cameraRightLength > 0.0f)
	{

		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;

	}

	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX+ cameraFrontZ * cameraFrontZ);

	if (cameraFrontLength > 0.0f)
	{
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
	}

	DirectX::XMFLOAT3 vec;
	vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
	vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);

	vec.y = 0.0f;

	return vec;
}
void Player::OnLanding()
{
	jumpCount = 0;
}
void Player::InputJump()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButton() & GamePad::BTN_A)
	{
		if(jumpCount < jumpLimit)
		{
			Jump(jumpSpeed);
			jumpCount++;
		}
	}
}
void Player::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	Character::RenderDebugPrimitive(rc, renderer);
	projectileManager.RenderDebugPrimitive(rc, renderer);
}
void Player::InputProjectile()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_B)
	{
		// 前方向 
		DirectX::XMFLOAT3 dir;
		dir.x = sinf(angle.y);
		dir.y = 0.0f;
		dir.z = cosf(angle.y);
		// 発射位置（プレイヤーの腰あたり） 
		DirectX::XMFLOAT3 pos;
		pos.x = position.x;
		pos.y = position.y + 1.0f;
		pos.z = position.z;
		// 発射 
		ProjectileStraight* projectile = new ProjectileStraight(&projectileManager);
		projectile->Launch(dir, pos);
		/*projectileManager.Register(projectile);*/

	}
}