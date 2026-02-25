#include "Base.h"
#include "Stage.h"
#include "Player.h"
#include <DxLib.h>
#include "Input.h"
#include "Bullet.h"
//#include "Enemy.h"
#include "NewEnemy.h"
#include "ExplosionEffect.h"
#include "ObjectManager.h"

namespace {
    
    ObjectManager& objManager = ObjectManager::GetInstance();
    //std::vector<Base*> objects;
    // std::vector<ExplosionEffect*> effects;

    // void RemoveObject(Base* obj) {}

    // ---- 初期パラメータ ----
	const Vector2D START_POS = Vector2D((float)(WIN_WIDTH / 2), (float)(WIN_HEIGHT / 2)); //初期位置（画面中央）
	const Vector2D START_VEL = Vector2D(0.0f, 0.0f);  // 初期速度（ゼロ）
    const Vector2D START_DIR = Vector2D(0.0f, -1.0f); //初期の向き（上向き）
    constexpr float RADIUS = 20.0f; // 形状
    constexpr float OMEGA = 2.0f; // 回転速度（rad/sec）
	const unsigned int COLOR = GetColor(255, 0, 0); // 赤
    const float PLAYER_COLLSTION_RADI = 15.0f;
}

namespace BulletParams {
    constexpr float SPEED = 600.0f;          // 速度
    const unsigned int COLOR = GetColor(255, 255, 255); // 白
    constexpr float RADIUS = 2.0f;           // 半径
    constexpr float LIFE = 3.0f;             // 寿命（秒）
}

namespace EnemyParams {
    constexpr int ENEMY_MAX = 50;

    // 見た目
    constexpr int   SEGMENTS_MIN = 12;
    constexpr int   SEGMENTS_MAX = 20;
    constexpr float JITTER_MIN = 0.25f;
    constexpr float JITTER_MAX = 0.45f;

    // サイズ
    constexpr float R_MIN = 25.0f;
    constexpr float R_MAX = 60.0f;

    // 移動
    constexpr float SPEED_MIN = 80.0f;
    constexpr float SPEED_MAX = 220.0f;

    // 回転
    constexpr float OMEGA_MIN = -1.2f; // rad/sec
    constexpr float OMEGA_MAX = 1.2f;

    inline unsigned int COLOR() {
        return GetColor(180, 180, 180);
    }

    inline float Rand01() {
        return (float)GetRand(10000) / 10000.0f;
    }

    inline float RandRange(float a, float b) {
        return a + (b - a) * Rand01();
    }

    inline int RandRangeInt(int a, int b) {
        return a + GetRand(b - a);
    }
}


Stage::Stage()
    : player_(nullptr) {}

void Stage::Initialize() {
    Release();
    score_ = 0;

    //変数playerだと、消えるので、newする
    player_ = new Player(
		START_POS, START_VEL, COLOR, START_DIR, RADIUS, OMEGA
	);
    player_->SetCollstionRadius(PLAYER_COLLSTION_RADI);
    objManager.AddObject(player_);

    for (int i = 0; i < EnemyParams::ENEMY_MAX; ++i) {
        SpawnEnemy();
    }
}

// Stage.h にデストラクタ宣言が無くても、暗黙デストラクタをここで定義できる
Stage::~Stage() {
    delete player_;
    player_ = nullptr;
}

void Stage::Update() {

    //各オブジェクトのアップデート処理
    //for (auto& effect : effects) effect->Update(); // エフェクト
    //for (auto& bullet : bullets_) bullet->Update(); //弾
    objManager.UpdateObject();

    // キーによる処理
    if (Input::IsKeyDown(KEY_INPUT_Z)) SpawnBullet(); //Zキーで、弾を発射する
    if (Input::IsKeyDown(KEY_INPUT_E)) SpawnEnemy(); //Eキーで、敵を出す 

	Enemy_vs_Bullet(); //敵と弾の当たり判定
    auto& bullets__ = objManager.GetGameObjects<Bullet>();
    for (int n = 0; n < bullets__.size(); n++) {
        Bullet* bullet = bullets__.at(n);
        if (!bullet->IsAlive()) {
            objManager.RemoveObject(bullet);
        }
    }
    
    // 寿命で削除
    //bullets_.erase(
    //    std::remove_if(bullets_.begin(), bullets_.end(),
    //        [](const Bullet* b) { return b->IsDead(); }),
    //    bullets_.end()
    //);
}

void Stage::SpawnBullet() {
    if (player_ == nullptr) return;

    Vector2D dir = player_->GetDirVec();
    Vector2D pos = player_->GetPos();

    // 発射位置を少し前へ（自分の半径＋少し）
    const float offset = player_->GetRadius() + 8.0f;
    pos.x += dir.x * offset;
    pos.y += dir.y * offset;

    Vector2D vel;
    vel.x = dir.x * BulletParams::SPEED;
    vel.y = dir.y * BulletParams::SPEED;

    objManager.AddObject(new Bullet(pos, vel, BulletParams::COLOR, BulletParams::RADIUS, BulletParams::LIFE));
}

void Stage::SpawnEnemy() {
    // 画面端付近から湧かせる（中心湧きよりゲームっぽい）
    const float W = (float)WIN_WIDTH;
    const float H = (float)WIN_HEIGHT;

    Vector2D pos;
    int side = GetRand(3); // 0..3
    if (side == 0) { pos.x = 0.0f; pos.y = EnemyParams::RandRange(0.0f, H); }
    if (side == 1) { pos.x = W;    pos.y = EnemyParams::RandRange(0.0f, H); }
    if (side == 2) { pos.x = EnemyParams::RandRange(0.0f, W); pos.y = 0.0f; }
    if (side == 3) { pos.x = EnemyParams::RandRange(0.0f, W); pos.y = H; }

    // 速度：ランダム方向
    float ang = EnemyParams::RandRange(0.0f, 6.2831853072f);
    float spd = EnemyParams::RandRange(EnemyParams::SPEED_MIN, EnemyParams::SPEED_MAX);
    Vector2D vel(std::cos(ang) * spd, std::sin(ang) * spd);
    int segments = EnemyParams::RandRangeInt(EnemyParams::SEGMENTS_MIN, EnemyParams::SEGMENTS_MAX);

    objManager.AddObject(new NewEnemy(Size::MEDIUM, 8));
}

void Stage::RandomSpawnEnemy(NewEnemy* enemy, int count, int size) {
    for (int n = 0; n < count; n++) { // 大サイズの場合、中サイズ2体を出す
        NewEnemy* newEnemy = new NewEnemy((Size) size, 8);
        Vector2D randomVel = { (float)(GetRand(200) - 100), (float)(GetRand(200) - 100) };
        newEnemy->SetPos(enemy->GetPos());
        newEnemy->SetVel(randomVel);
        objManager.AddObject(newEnemy);
    }
    objManager.RemoveObject(enemy);
    //RemoveEnemy(enemy);
}

void Stage::Enemy_vs_Bullet() {
    // Update enemies
    auto& enemies_ = objManager.GetGameObjects<NewEnemy>();
    auto& bullets_ = objManager.GetGameObjects<Bullet>();
    for (int n = 0; n < enemies_.size(); n++) {
        NewEnemy* enemy = enemies_.at(n);
        if (enemy == nullptr) continue;
        if (!enemy->IsAlive()) continue;
        enemy->Update();

        Player_vs_Enemy();

        // 弾と敵の当たり判定
        for (Bullet* b : bullets_) {
            float distance = Math2D::Length(Math2D::Sub(b->GetPos(), enemy->GetPos())); //弾と敵の距離
            Vector2D enemyPos = enemy->GetPos();
            Size enemySize = enemy->GetSize();

            if (distance < b->Radius() + enemy->Radius()) {
                int num = GetRand(3) + 2;
                int sc[3] = { 20, 50, 100 };
                score_ += sc[enemy->GetSize()];

                if (enemySize == Size::SMALL) { //小サイズの場合、弾が当たったら消える               
                    objManager.AddObject(new ExplosionEffect(enemyPos));
                    //RemoveEnemy(enemy);
                    objManager.RemoveObject(enemy);
                }
                else if (enemySize == Size::MEDIUM) { //中サイズの場合、小サイズ2体を出す
                    RandomSpawnEnemy(enemy, num, Size::SMALL);
                }
                else if (enemySize == Size::LARGE) { //
                    RandomSpawnEnemy(enemy, num, Size::MEDIUM);
                }
                b->Dead();           // 弾を消す
            }
        }
    }

}

void Stage::Player_vs_Enemy() {
	auto& enemies_ = objManager.GetGameObjects<NewEnemy>();
    player_->isHit = false; 
    for (auto& enemy : enemies_) {
		auto& pPos = player_->GetPos();
		auto& ePos = enemy->GetPos();
		// プレイヤーと敵の当たり判定
		float distance = Math2D::Length(Math2D::Sub(pPos, ePos)); //プレイヤーと敵の距離
		if (distance < player_->GetRadius() + enemy->Radius()) {
            player_->isHit = true;
            player_->isAlive_ = false;

            break;
		}
    }
}

void Stage::Draw() {   
    objManager.DrawObject();

    DrawFormatString(0, 0, GetColor(255, 255, 255), "スコア：%d", score_);
}

void Stage::Release() {
	if (player_)
	{
		delete player_;
		player_ = nullptr;
	}
}

//void Stage::DeleteBullet() {
//    auto& bullets_ = objManager.GetObjects<Bullet>();
//	for (auto it = bullets_.begin(); it != bullets_.end(); ) {
//		if ((*it)->IsDead()) {
//			delete* it; // メモリ解放
//			it = bullets_.erase(it); // イテレータを更新
//		}
//		else {
//			it++; // 次の要素へ
//		}
//	}
//}
//
//void Stage::RemoveEnemy(NewEnemy* enemy) {
//    enemy->Dead();
//    auto& enemies_ = objManager.GetObjects<NewEnemy>();
//    for (auto it = enemies_.begin(); it != enemies_.end(); ) {
//        if ((*it)->IsAlive()) {
//            it++; // 次の要素へ
//        }
//        else {
//            delete* it; // メモリ解放
//            it = enemies_.erase(it); // イテレータを更新
//        }
//    }
//}
