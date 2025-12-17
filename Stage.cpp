#include "Stage.h"
#include "Player.h"
#include <DxLib.h>
#include "Math2D.h"
#include "Bullet.h"
#include <vector>
#include "global.h"
#include "Input.h"

namespace {
	//プレイヤーの初期設定
	const Vector2D startPos = { 600.0f, 600.0f };
	const Vector2D startVel = { 0.0f, 0.0f };
	const float startRadius = 60.0f;
	const float startOmega = 1.0f;
	const float startAngles = 0.0f;
	const Vector2D startDir = { 0.0f, -1.0f };
	const unsigned int startColor = GetColor(255, 0, 0);
	Player* player = nullptr;
	std::vector<Bullet*> bullets;
}

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	player->Draw();

	for (auto bullet : bullets) {
		bullet->Draw();
	}
}

void Stage::Initialize()
{
	player = new Player(startPos, startVel, startDir, startRadius, startOmega, 
		startAngles, startColor, SHAPE::CIRLCE);
}

void Stage::Update()
{
	for (auto it = bullets.begin(); it != bullets.end();) {
		if ((*it)->IsDead()) {
			bullets.erase(it);
		}
		else {
			it++;
		}
	}

	player->Update();
	if (!bullets.empty()) { //
		for (auto& itr : bullets) {
			itr->Update();
		}
	}

	if (Input::IsKeyDown(KEY_INPUT_Z)) {
		Vector2D pos = player->GetPos();
		Vector2D bulletVelocity = Math2D::Mul(player->GetDirVec(), 500.0f); //プレイヤーの向きの倍の速度
		unsigned int bulletColor = GetColor(255, 255, 255);
		float r = 2;
		float life = 2.0f;

		Bullet* bullet = new Bullet(pos, bulletVelocity, bulletColor, SHAPE::CIRLCE);
		bullets.push_back(bullet);
	}
}

void Stage::Release()
{
}
