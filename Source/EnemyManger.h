#pragma once

#include <vector>
#include "Enemy.h"

class EnemyManager
{
private:
	EnemyManager(){}
	~EnemyManager(){}
	std::vector<Enemy*>enemies;
	void CollisionEnemyVsEnemies();

public:

	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}
	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void Register(Enemy* enemy);

	void  RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	void Clear();

	int GetEnemyCount() const { return static_cast<int>(enemies.size()); }

	Enemy* GetEnemy(int index) { return enemies.at(index); }
//private:
//	std::vector<Enemy*>enemies;

};