#include "NewEnemy.h"
#include <DxLib.h>
#include "globals.h"

namespace {
	const int SEGMENT_MIN = 8;
	const float MIN_RADIUS = 25.0f;
}

NewEnemy::NewEnemy(int segment)
 : Base(), segment_(segment){
	pos_ = { GetRand(WIN_WIDTH - 1), GetRand(WIN_HEIGHT - 1) };
	vel_ = { (float)(GetRand(200) - 100), (float)(GetRand(200) - 100)};
	Color_ = GetColor(255, 255, 255);
	if (segment_ < SEGMENT_MIN) {
		segment_ = SEGMENT_MIN; //最低8分割
	}
	radius_ = (float)(GetRand(50) + MIN_RADIUS); //25～75の半径
	vertex_.resize(segment_);
}

void NewEnemy::Update()
{
}

void NewEnemy::Draw() {
	std::vector<Vector2D> scrPos(segment_);
	for(int i = 0; i < segment_; i++) {
		scrPos[i] = Math2D::World2Screen(vertex_[i]); //頂点をスクリーン座標に変換
	}

	for (int i = 0; i < segment_; i++) {
		int next = (i + 1) % segment_;
		DrawLineAA(
			scrPos[i].x, scrPos[i].y,
			scrPos[next].x, scrPos[next].y,
			Color_, 2.0f
		);
	}
	MakeShape();
}

void NewEnemy::MakeShape() {
	for (int i = 0; i < segment_; i++) {
		float angle = (2.0f * DX_PI / (float)segment_) * (float)i;
		vertex_[i] = { cosf(angle) * radius_, 
			sinf(angle) * radius_ };
		pos_ = Math2D::Add(vertex_[i], pos_); //ワールド座標に変換
	}
}
