#pragma once
#include "BaseChara.h"
#include "Math2D.h"

class Player : public BaseChara {
private:
	Vector2D direction_; //Œü‚«ƒxƒNƒgƒ‹
	float radius_; //”¼Œa
	Vector2D vertex_[3]; //OŠpŒ`‚Ì’¸“_À•W
	float omega_; //‰ñ“]‘¬“x
	float angles_; //‰ñ“]Šp
public:
	Player();
	Player(const Vector2D& pos, const Vector2D& vel, const Vector2D& dire, float radius, float omega, float angles, unsigned int color, SHAPE shape);
	~Player();

	void SetDirVec(const Vector2D& dire) { direction_ = dire; };
	Vector2D GetDirVec() const { return direction_; }
	void SetRadius(float r) { radius_ = r; }
	float GetRadiut() { return radius_; }
	void SetOmega(float omega) { omega_ = omega; }
	float GetOmega() { return omega_; }
	void SetAngle(float angle) { angles_ = angle; }
	float GetAngle() { return angles_; }

	void Draw() override;
	void Update() override;

};

