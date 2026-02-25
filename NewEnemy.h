#pragma once
#include "Base.h"
#include <vector>

enum Size {
	LARGE,
	MEDIUM,
	SMALL
};

class NewEnemy : public Base {
private:
	int segment_; //分割数
	float angle_;
	float omega_;
	int radius_;
	std::vector<Vector2D> vertex_;
	Size size_;
public:
	//NewEnemy(int segment);
	NewEnemy(Size size, int segment);
	//NewEnemy(const Vector2D& pos, const Vector2D& vel, Size size, int segment);

	void Update() override;
	void Draw() override;
	void MakeShape();
	void Dead();
	float RandomRadius(Size size); //サイズに応じたランダム半径取得
	int Radius() const { return radius_; };
	Size GetSize() const { return size_; };
	Size CheckSize() const;
};

