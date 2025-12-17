#pragma once
#include "BaseChara.h"

class Bullet : BaseChara{
private:
	float lifeTime_;
	float radius_;
public:
	Bullet();
	Bullet(const Vector2D& pos, const Vector2D& vel, unsigned int color, SHAPE shape);
	~Bullet();
	void Draw() override;
	void Update() override;

	bool IsDead() const { return lifeTime_ <= 0; };
	float GetRadius() const { return radius_; };
};

