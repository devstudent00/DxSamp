#include "Player.h"
#include "BaseChara.h"
#include <DxLib.h>
#include <cmath>
#include "global.h"
#include "Math2D.h"
#include "Input.h"

namespace {
	const float PI = 3.141592;
	const float DAMP = 0.98f; //減衰率
	const float ACC = 200.0f; //加速度
}

Player::Player()
 :BaseChara(Vector2D(0,0), Vector2D(0,0), GetColor(0,0,0), SHAPE::CIRLCE),
	direction_({ 0, -1 }), radius_(1.0f), omega_{ 1.0f }, angles_{0.0f} {
	vertex_[0] = {0, 0};
	vertex_[0] = { 0, 1 };
	vertex_[0] = { 0, 2};
}

Player::Player(const Vector2D& pos, const Vector2D& vel, const Vector2D& dire, float radius, float omega, float angles, unsigned int color, SHAPE shape)
 :BaseChara(pos, vel, color, SHAPE::CIRLCE), direction_(dire), radius_(radius), omega_(omega), angles_(angles){
	vertex_[0] = { 0, 0 };
	vertex_[1] = { 0, 0 };
	vertex_[2] = { 0, 0};
}

Player::~Player() {
}

void Player::Draw() {
	Vector2D scrPos[3];
	for (int i = 0; i < 3; ++i) {
		scrPos[i] = Math2D::WorldToScreen(vertex_[i]);
	}
	DrawTriangleAA(
		vertex_[0].x, scrPos[0].y,
		vertex_[1].x, scrPos[1].y,
		vertex_[2].x, scrPos[2].y,
		GetColor(255,0,0), true);

	//回転できる三角形の描画

	//メッセージ
	DrawFormatString(0, 0, GetColor(0, 0, 0), "angles: %lf", angles_);
}

void Player::Update() {
	//キーによる回転
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT)) {
		angles_ = angles_ + omega_ * GetDeltaTime();
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT)) {
		angles_ = angles_ - omega_ * GetDeltaTime();
	}

	//原点にある半径1の正三角形の頂点座標を求める
	Vector2D p[3];
	p[0] = { 0, 1 };
	p[1] = { cos(-60.0f * (PI / 180.0f)), sin(-60.0f * (PI / 180.0f)) };
	p[2] = { cos(240.0f * (PI / 180.0f)), sin(240.0f * (PI / 180.0f)) };

	//半径を1から、radius倍にする
	p[0].x = radius_ * p[0].x; p[0].y = radius_ * p[0].y;
	p[1].x = radius_ * p[1].x; p[1].y = radius_ * p[1].y;
	p[2].x = radius_ * p[2].x; p[2].y = radius_ * p[2].y;

	vertex_[0] = { pos_.x + p[0].x, pos_.y + p[0].y };
	vertex_[1] = { pos_.x + p[1].x, pos_.y + p[1].y };
	vertex_[2] = { pos_.x + p[2].x, pos_.y + p[2].y };

	//回転行列を作成
	Mat2 rotMat(
		cos(angles_), -sin(angles_),
		sin(angles_), cos(angles_),
		0.0f, 0.0f
	);
	//回転行列を各頂点に適用
	for (int i = 0; i < 3; ++i) {
		Vector2D v = Math2D::Sub(vertex_[i], pos_);
		Vector2D rotatedV = Math2D::TransformPoint(v, rotMat);;
		rotatedV = Math2D::Add(rotatedV, pos_);
		vertex_[i] = rotatedV;
	}
	//3角形の3頂点をdir_とradius_とpos_から求めよう
	direction_ = Math2D::FromAngle(angles_ + PI / 2.0f);
	pos_.x = pos_.x + direction_.x * vel_.x * GetDeltaTime();
	pos_.y = pos_.y + direction_.y * vel_.y * GetDeltaTime();





	//vertex_[0] = { pos_.x + p[0].x, pos_.y + radius_};
	//vertex_[1] = { pos_.x + radius_ * cos(-60.0f * (PI / 180.0f)),
	//				pos_.y + radius_*sin(-60.0f * (PI / 180.0f))};
	//vertex_[2] = { pos_.x + radius_ * cos(240.0f * (PI / 180.0f)),
	//				pos_.y + radius_ * sin(240.0f * (PI / 180.0f)) };
}
