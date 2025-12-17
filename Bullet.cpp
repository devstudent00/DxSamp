#include "Bullet.h"
#include <DxLib.h>
#include "Math2D.h"
#include "global.h"

Bullet::Bullet() {
}

Bullet::Bullet(const Vector2D& pos, const Vector2D& vel, unsigned int color, SHAPE shape)
 : BaseChara(pos, vel, color, shape), lifeTime_(300), radius_(10){
}

Bullet::~Bullet()
{
}

void Bullet::Draw()
{
	Vector2D screenPos = Math2D::WorldToScreen(pos_);
	DrawCircle(screenPos.x, screenPos.y, radius_, true, true);
}

void Bullet::Update()
{
	float dt = GetDeltaTime();
	pos_ = Math2D::Add(pos_, Math2D::Mul(vel_, dt));
}
