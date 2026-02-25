#include "NewEnemy.h"
#include <DxLib.h>
#include "globals.h"

namespace {
	const int SEGMENT_MIN = 8; //最小分割数
	const float MIN_RADIUS = 25.0f; //最小半径
	const float MAX_OMEGA = 2.0f; //最大角速度

	//サイズ定数
	const float SMALL_RADIUS_MIN = 20.0f; //小サイズの最小半径
	const float SMALL_RADIUS_MAX = 40.0f; //小サイズの最大半径
	const float MEDIUM_RADIUS_MIN = 40.0f; //中サイズの最小半径
	const float MEDIUM_RADIUS_MAX = 60.0f; //中サイズの最大半径
	const float LARGE_RADIUS_MIN = 60.0f; //大サイズの最小半径
	const float LARGE_RADIUS_MAX = 80.0f; //大サイズの最大半径
}

//NewEnemy::NewEnemy(int segment)
// : Base(), segment_(segment){
//	isAlive_ = true;
//	pos_ = { (float) GetRand(WIN_WIDTH - 1), (float) GetRand(WIN_HEIGHT - 1) };
//	vel_ = { (float)(GetRand(200) - 100), (float)(GetRand(200) - 100)};
//	Color_ = GetColor(255, 255, 255);
//	if (segment_ < SEGMENT_MIN) {
//		segment_ = SEGMENT_MIN; //最低8分割
//	}
//	radius_ = (float)(GetRand(50) + MIN_RADIUS); //25～75の半径
//	size_ = CheckSize();
//	vertex_.resize(segment_);
//
//	angle_ = 0.0f;
//	omega_ = (float)(GetRand(200) - 100) / 100.0f; //-1.0～1.0の角速度
//
//	MakeShape();
//}
//
NewEnemy::NewEnemy(Size size, int segment)
	: Base(), segment_(segment), size_(size) {
	isAlive_ = true;
	pos_ = { (float)GetRand(WIN_WIDTH - 1), (float)GetRand(WIN_HEIGHT - 1) };
	vel_ = { (float)(GetRand(200) - 100), (float)(GetRand(200) - 100) };
	Color_ = GetColor(255, 255, 255);
	if (segment_ < SEGMENT_MIN) {
		segment_ = SEGMENT_MIN; //最低8分割
	}
	radius_ = (int)RandomRadius(size_); //サイズに応じた半径
	vertex_.resize(segment_); //配列のサイズを変更する
	angle_ = 0.0f;
	omega_ = (float)(GetRand(200) - 100) / 100.0f; //-1.0～1.0の角速度

	MakeShape();
}

//NewEnemy::NewEnemy(const Vector2D& pos, const Vector2D& vel, Size size, int segment)
// : Base(pos, vel, GetColor(255, 255, 255)), segment_(segment),  size_(size) {
//	isAlive_ = true;
//	if (segment_ < SEGMENT_MIN) {
//		segment_ = SEGMENT_MIN; //最低8分割
//	}
//	radius_ = (int)RandomRadius(size_); //サイズに応じた半径
//	vertex_.resize(segment_); //配列のサイズを変更する
//	angle_ = 0.0f;
//	omega_ = (float)(GetRand(200) - 100) / 100.0f; //-1.0～1.0の角速度
//
//	MakeShape();
//}

void NewEnemy::Update()
{
	if (!isAlive_) return;
	float dt = GetDeltaTime();
	pos_ = Math2D::Add(pos_, Math2D::Mul(vel_, dt));

	//画面外に出たら反対側から出現
	if (pos_.x < 0) pos_.x = (float)WIN_WIDTH;
	if (pos_.x > WIN_WIDTH) pos_.x = 0.0f;
	if (pos_.y < 0) pos_.y = (float)WIN_HEIGHT;
	if (pos_.y > WIN_HEIGHT) pos_.y = 0.0f;

	angle_ = angle_ + omega_ * dt;

	//当たり判定

}

void NewEnemy::Draw() {
	if (!isAlive_) return;
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
		// 半径にランダム性を加える例
		float length = radius_ / 2.0f + GetRand(10); 
		vertex_[i] = { cosf(angle) * length, sinf(angle) * length };
	}
}

void NewEnemy::Dead() {
	isAlive_ = false;
}

float NewEnemy::RandomRadius(Size size){
	switch (size) {
	case Size::SMALL:
		return GetRand((SMALL_RADIUS_MAX - SMALL_RADIUS_MIN)) + SMALL_RADIUS_MIN; //GetRand(40.0 - 20.0) + 20.0：0~20 → 20~40
	case Size::MEDIUM:
		return GetRand((MEDIUM_RADIUS_MAX - MEDIUM_RADIUS_MIN)) + MEDIUM_RADIUS_MIN; //GetRand(60.0 - 40.0) + 40.0：0~20 → 40~60;
	case Size::LARGE:
		return GetRand((LARGE_RADIUS_MAX - LARGE_RADIUS_MIN)) + LARGE_RADIUS_MIN; //GetRand(80.0 - 60.0) + 60.0：0~20 → 60~80;
	default:
		return 1.0f;
	}
}

Size NewEnemy::CheckSize() const
{
	if (radius_ <= SMALL_RADIUS_MAX) { //例：40.0f(半径) <= 40.0f(小サイズ)
		return Size::SMALL;
	}
	else if (radius_ <= MEDIUM_RADIUS_MAX) { //例：50.0f(半径) <= 60.0f(中サイズ)
		return Size::MEDIUM;
	}
	else { 
		return Size::LARGE;
	}
}
