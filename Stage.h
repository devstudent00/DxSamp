#pragma once
#include <vector>

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
    void DeleteBullet();
private:
    void SpawnBullet();   // ”­Ëˆ—iZ‰Ÿ‰ºj
	void SpawnEnemy();    // “G¶¬ˆ—
private:
    Player* player_;
    std::vector<Bullet *> bullets_;
    std::vector<NewEnemy*> enemies_;
};

