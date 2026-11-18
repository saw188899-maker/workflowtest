#include "System/Graphics.h"
#include "SceneGame.h"
#include"Camera.h"
#include"camera controller.h"
#include"EnemyManger.h"
#include"EnemySlime.h"

// 初期化
void SceneGame::Initialize()
{
	stage = new Stage();
	player = new Player();
	cameraController = new CameraController();
	//Camera
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAT(
		DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	//Enemy
	EnemyManager& enemyManager = EnemyManager::Instance();

	/*EnemySlime* slime = new EnemySlime();

	slime->SetPosition(DirectX::XMFLOAT3(0, 0, 5));

	enemyManager.Register(slime);*/

	for (int i = 0; i < 2; ++i)
	{
		EnemySlime* slime = new EnemySlime();
		slime->SetPosition(DirectX::XMFLOAT3(i * 2.0f, 0, 5));
		enemyManager.Register(slime);
	}
}

// 終了化
void SceneGame::Finalize()
{
	//camera controller
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}
	if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	DirectX::XMFLOAT3 target = player-> GetPosition();

	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);

	stage->Update(elapsedTime);

	player->Update(elapsedTime);

	//Enemy
	EnemyManager::Instance().Update(elapsedTime);
}

// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ShapeRenderer* shapeRenderer = graphics.GetShapeRenderer();
	ModelRenderer* modelRenderer = graphics.GetModelRenderer();

	// 描画準備
	RenderContext rc;
	rc.deviceContext = dc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f };	// ライト方向（下方向）
	rc.renderState = graphics.GetRenderState();

	//camera view
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	// ビュー行列
	//{
	//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// カメラの視点（位置）
	//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// カメラの注視点（ターゲット）
	//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// カメラの上方向

	//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	//	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
	//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	//	DirectX::XMStoreFloat4x4(&rc.view, View);
	//}
	// プロジェクション行列
	//{
	//	float fovY = DirectX::XMConvertToRadians(45);	// 視野角
	//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// 画面縦横比率
	//	float nearZ = 0.1f;	// カメラが映し出すの最近距離
	//	float farZ = 1000.0f;	// カメラが映し出すの最遠距離
	//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
	//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
	//}

	// 3Dモデル描画
	{
		stage->Render(rc, modelRenderer);
	
		player->Render(rc, modelRenderer);

		EnemyManager::Instance().Render(rc, modelRenderer);
	}

	// 3Dデバッグ描画
	{
		player->DrawDebugGUI();

		player->RenderDebugPrimitive(rc,shapeRenderer );

		EnemyManager::Instance().RenderDebugPrimitive(rc, shapeRenderer);

	}

	// 2Dスプライト描画
	{

	}
}

// GUI描画
void SceneGame::DrawGUI()
{
	//Player Debug
	player-> DrawDebugGUI();
}
