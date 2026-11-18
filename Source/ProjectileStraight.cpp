#include "ProjectileStraight.h"

//コンストラクタ
ProjectileStraight::ProjectileStraight(ProjectileManager* manager)
	: Projectile(manager)
{
	/*model = new Model("Data/Model/SpikeBall/SpikeBall.mdl");
	scale.x = scale.y = scale.z = 0.5f;*/

	model = new Model("Data/Model/Sword/Sword.mdl");
	scale.x = scale.y = scale.z = 3.0f;
}
//デストラクタ
ProjectileStraight::~ProjectileStraight()
{
	delete model;
}
void ProjectileStraight::Update(float elapsedTime)
{
	//寿命
	lifeTime -= elapsedTime;
	if(lifeTime <= 0.0f)
	{
		Destroy();
	}
	//移動
	float speed = this->speed * elapsedTime;
	position.x += direction.x * speed;
	position.y += direction.y * speed;
	position.z += direction.z * speed;

	UpdateTransform();
	model->UpdateTransform();

}
void ProjectileStraight::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}
void ProjectileStraight::Launch(const DirectX::XMFLOAT3& direction, 
								const DirectX::XMFLOAT3& position)
{
	this->direction = direction;
	this->position = position;
}