#include "Player.h"
#include "BaseChara.h"

Player::Player(const Vector2D& pos, const Vector2D& vel, unsigned int color, SHAPE shape, int size)
 : BaseChara(pos, vel, color, shape), size_(size) {
	
}

Player::~Player() {
}

void Player::Draw() {

}

void Player::Update()
{
}
