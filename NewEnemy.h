#pragma once
#include "Base.h"
#include <vector>

class NewEnemy : public Base {
private:
	int segment_;
	int radius_;
	std::vector<Vector2D> vertex_;
public:
	NewEnemy(int segment);
	void Update() override;
	void Draw() override;
	void MakeShape();
};

