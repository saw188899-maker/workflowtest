#include "Projectile.h"
#include "ProjectileManager.h"

//コンストラクタ
Projectile::Projectile(ProjectileManager* manager)
{
	manager->Register(this);
}
void Projectile::Destroy()
{
	manager->Remove(this);
}

void Projectile::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
}

//行列更新	
void Projectile::UpdateTransform()
{
	transform._11 = 1.0f * scale.x;
	transform._12 = 0.0f * scale.x;
	transform._13 = 0.0f * scale.x;
	transform._14 = 0.0f ;
	transform._21 = 0.0f * scale.y;
	transform._22 = 1.0f * scale.y;
	transform._23 = 0.0f * scale.y;
	transform._24 = 0.0f;
	transform._31 = 0.0f * scale.z;
	transform._32 = 0.0f * scale.z;
	transform._33 = 1.0f * scale.z;
	transform._34 = 0.0f;
	transform._41 = position.x;
	transform._42 = position.y;
	transform._43 = position.z;
	transform._44 = 1.0f;

}