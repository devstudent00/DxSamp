#include "Player.h"
#include "BaseChara.h"
#include <DxLib.h>
#include <cmath>
#include "global.h"
#include "Math2D.h"

namespace {
	const float PI = 3.141592;

	Vector2D WorldToScreen(const Vector2D& worldPos) {
		return Vector2D(worldPos.x, WIN_HEIGHT - worldPos.y);
	}
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
		scrPos[i] = WorldToScreen(vertex_[i]);
	}
	DrawTriangleAA(
		vertex_[0].x, scrPos[0].y,
		vertex_[1].x, scrPos[1].y,
		vertex_[2].x, scrPos[2].y,
		GetColor(255,0,0), true);
}

void Player::Update()
{
	//Œ´“_‚É‚ ‚é”¼Œa1‚Ì³ŽOŠpŒ`‚Ì’¸“_À•W‚ð‹‚ß‚é
	Vector2D p[3];
	p[0] = { 0, 1 };
	p[1] = { cos(-60.0f * (PI / 180.0f)), sin(-60.0f * (PI / 180.0f)) };
	p[2] = { cos(240.0f * (PI / 180.0f)), sin(240.0f * (PI / 180.0f)) };

	//”¼Œa‚ð1‚©‚çAradius”{‚É‚·‚é
	p[0].x = radius_ * p[0].x; p[0].y = radius_ * p[0].y;
	p[1].x = radius_ * p[1].x; p[1].y = radius_ * p[1].y;
	p[2].x = radius_ * p[2].x; p[2].y = radius_ * p[2].y;

	vertex_[0] = { pos_.x + p[0].x, pos_.y + p[0].y };
	vertex_[1] = { pos_.x + p[1].x, pos_.y + p[1].y };
	vertex_[2] = { pos_.x + p[2].x, pos_.y + p[2].y };



	//vertex_[0] = { pos_.x + p[0].x, pos_.y + radius_};
	//vertex_[1] = { pos_.x + radius_ * cos(-60.0f * (PI / 180.0f)),
	//				pos_.y + radius_*sin(-60.0f * (PI / 180.0f))};
	//vertex_[2] = { pos_.x + radius_ * cos(240.0f * (PI / 180.0f)),
	//				pos_.y + radius_ * sin(240.0f * (PI / 180.0f)) };
}
