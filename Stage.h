#pragma once
#include <vector>

enum GameStatus {
	TITLE,
	PLAYING,
	GAMEOVER
};

class Bullet;
class Player;
//class Enemy;
class NewEnemy;
class Stage
{
public:
    Stage();
	~Stage();
	void Initialize();
    void Update();
    void Draw();
	void Release();
    //void DeleteBullet();
    //void RemoveEnemy(NewEnemy* enemy);

    void SpawnBullet();   // 発射処理（Z押下）
    void SpawnEnemy();    // 敵生成処理

    /// <summary>
    /// 分裂用の敵をスポーンさせる関数
    /// </summary>
    /// <param name="enemy">適のポインタ</param>
    /// <param name="count">敵の数</param>
    /// <param name="size">敵の数（Enumで指定する）</param>
    void RandomSpawnEnemy(NewEnemy* enemy, int count, int size);
private:

private:
	GameStatus gameStatus_;
    Player* player_;
    long long score_;
	void Enemy_vs_Bullet();
    ///std::vector<Bullet *> bullets_;
    //std::vector<NewEnemy*> enemies_;
};