#pragma once
 
#include "Projectile.h"
#include <vector>
#include <set>

//弾丸マネージャー
class ProjectileManager
{
public:
	ProjectileManager() ;
	~ProjectileManager() ;

	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	void Register(Projectile* projectile);

	void clear();

	int GetProjectileCount() const { return static_cast<int>(projectiles.size()); }

	Projectile* GetProjectile(int index) { return projectiles[index]; }

	void Remove(Projectile* projectile);

private:
	std::vector<Projectile*> projectiles;
	std::set<Projectile*> removes;
};