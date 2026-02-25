#pragma once
#include "Base.h"
#include <vector>

class ExplosionEffect : public Base {
public:
	
	ExplosionEffect(Vector2D pos, int particleCount = 20);

	void Update() override;
	void Draw() override;

	

	bool IsFinished() const { return isFinished_; }

	struct Particle {
		float alpha;
		Vector2D offset_; //位置
		Vector2D velocity; //速度
		float life; //寿命
		float radius; //判定
	};
private:
	bool isFinished_; //エフェクト終了フラグ
	std::vector<Particle> particles_;  //パーティクル
	unsigned int CharColor_;
};

