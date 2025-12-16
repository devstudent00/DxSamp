#pragma once
#include "BaseChara.h"
#include "Vector2D.h"

class Player : public BaseChara {
private:
	Vector2D angle_;
	int size_;
public:
	Player(const Vector2D& pos, const Vector2D& vel, unsigned int color, SHAPE shape, int size);
	~Player();

	void Draw() override;
	void Update() override;
};

