#pragma once
#include "Base.h"
#include <vector>

class NewEnemy : public Base {
private:
	int segment_; //•ªŠ„”
	float angle_;
	float omega_;
	int radius_;
	bool isAlive_; //¶‘¶ƒtƒ‰ƒOAtrue‚È‚ç¶‘¶
	std::vector<Vector2D> vertex_;
public:
	NewEnemy(int segment);
	void Update() override;
	void Draw() override;
	void MakeShape();
	bool IsAlive() const { return isAlive_; };
};

