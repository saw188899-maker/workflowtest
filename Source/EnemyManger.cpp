#include "EnemyManger.h"
#include "Collision.h"

void EnemyManager::Update(float elapsedTime)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Update(elapsedTime);
	}
	CollisionEnemyVsEnemies();
}

void EnemyManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Render(rc, renderer);
	}
}

void EnemyManager::Register(Enemy* enemy)
{
	enemies.emplace_back(enemy);
}

void EnemyManager::Clear()
{
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
}

void EnemyManager::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (Enemy* enemy : enemies)
	{
		enemy->RenderDebugPrimitive(rc, renderer);
	}
}
// エネミー同士の衝突処理
void EnemyManager::CollisionEnemyVsEnemies()
{
  
        Collision collision;

        size_t enemyCount = enemies.size();

        for (int i = 0; i < enemyCount; i++)
        {
            Enemy* enemyA = GetEnemy(i);

            for (int j = i + 1; j < enemyCount; j++)
            {
                Enemy* enemyB = GetEnemy(j);

                DirectX::XMFLOAT3 outPosition;

               /* if (collision.IntersectSphereVsSphere(
                    enemy1->GetPosition(),
                    enemy1->GetRadius(),
                    enemy2->GetPosition(),
                    enemy2->GetRadius(),
                    outPosition
                ))
                {
                    enemy2->SetPosition(outPosition);
                }*/
                if (Collision::IntersectCylinderVsCylinder(
                    enemyA->GetPosition(),
                    enemyA->GetRadius(),
                    enemyA->GetHeight(),
                    enemyB->GetPosition(),
                    enemyB->GetRadius(),
                    enemyB->GetHeight(),
                    outPosition
                ))
                {
                    enemyB->SetPosition(outPosition);
                }

            }
        }
    
}
