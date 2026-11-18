#include "EnemySlime.h"

EnemySlime::EnemySlime()
{
	model = new Model("Data/Model/Slime/Slime.mdl");

	scale.x = scale.y = scale.z = 0.01f;
	radius = 0.5f;
	height = 1.0f;
}

EnemySlime::~EnemySlime()
{
	delete model;
}
void EnemySlime::Update(float elapsedTime)
{
	UpdateVelocity(elapsedTime);
	UpdateTransform();
	model->UpdateTransform();

}
void EnemySlime::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}
