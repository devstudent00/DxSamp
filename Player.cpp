#include "Player.h"
#include "BaseChara.h"
#include <DxLib.h>
#include <cmath>

namespace {
	const float PI = 3.141592;
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
	vertex_[0] = { 0, 0 };
	vertex_[0] = { 0, 0};
}

Player::~Player() {
}

void Player::Draw() {
	DrawTriangleAA(
	vertex_[0].x, vertex_[0].y,
		vertex_[1].x, vertex_[1].y, 
		vertex_[2].x, vertex_[2].y, 
		GetColor(255,0,0), true);
}

void Player::Update()
{
	
	vertex_[0] = { pos_.x + 0, pos_.y + radius_ };
	vertex_[1] = { pos_.x + radius_ * cos(-60.0f * (PI / 180.0f)),
					pos_.y + radius_*sin(-60.0f * (PI / 180.0f))};
	vertex_[2] = { pos_.x + radius_ * cos(240.0f * (PI / 180.0f)),
					pos_.y + radius_ * sin(240.0f * (PI / 180.0f)) };
}
