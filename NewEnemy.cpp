#include "NewEnemy.h"
#include <DxLib.h>
#include "globals.h"

namespace {
	const int SEGMENT_MIN = 8;
	const float MIN_RADIUS = 25.0f;
}

NewEnemy::NewEnemy(int segment)
 : Base(), segment_(segment), isAlive_(true){
	pos_ = { (float) GetRand(WIN_WIDTH - 1), (float) GetRand(WIN_HEIGHT - 1) };
	vel_ = { (float)(GetRand(200) - 100), (float)(GetRand(200) - 100)};
	Color_ = GetColor(255, 255, 255);
	if (segment_ < SEGMENT_MIN) {
		segment_ = SEGMENT_MIN; //Å’á8•ªŠ„
	}
	radius_ = (float)(GetRand(50) + MIN_RADIUS); //25`75‚Ì”¼Œa
	vertex_.resize(segment_);

	angle_ = 0.0f;
	omega_ = (float)(GetRand(200) - 100) / 100.0f; //-1.0`1.0‚ÌŠp‘¬“x

	MakeShape();
}

void NewEnemy::Update()
{
	float dt = GetDeltaTime();
	pos_ = Math2D::Add(pos_, Math2D::Mul(vel_, dt));

	//‰æ–ÊŠO‚Éo‚½‚ç”½‘Î‘¤‚©‚çoŒ»
	if (pos_.x < 0) pos_.x = (float)WIN_WIDTH;
	if (pos_.x > WIN_WIDTH) pos_.x = 0.0f;
	if (pos_.y < 0) pos_.y = (float)WIN_HEIGHT;
	if (pos_.y > WIN_HEIGHT) pos_.y = 0.0f;

	angle_ = angle_ + omega_ * dt;

	//“–‚½‚è”»’è

}

void NewEnemy::Draw() {
	std::vector<Vector2D> scrPos(segment_);
	for(int i = 0; i < segment_; i++) {
		Vector2D worldPos = Math2D::Add(pos_, vertex_[i]);
		Mat2 rotMat = Math2D::Rotation(angle_);
		scrPos[i] = Math2D::TransformPoint(vertex_[i], rotMat);
		scrPos[i] = Math2D::Add(scrPos[i], pos_);
		scrPos[i] = Math2D::World2Screen(scrPos[i]);
		//scrPos[i] = Math2D::World2Screen(worldPos);
	}

	for (int i = 0; i < segment_; i++) {
		int next = (i + 1) % segment_;
		DrawLineAA(
			scrPos[i].x, scrPos[i].y,
			scrPos[next].x, scrPos[next].y,
			Color_, 2.0f
		);
	}
}

void NewEnemy::MakeShape() {
	for (int i = 0; i < segment_; i++) {
		float angle = (2.0f * DX_PI / (float)segment_) * (float)i;
		// ”¼Œa‚Éƒ‰ƒ“ƒ_ƒ€«‚ð‰Á‚¦‚é—á
		float length = radius_ / 2.0f + GetRand(10); 
		vertex_[i] = { cosf(angle) * length, sinf(angle) * length };
	}
}
