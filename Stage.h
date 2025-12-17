#pragma once
#include "Player.h"

class Stage {
public:
	Stage();
	~Stage();
	void Draw();
	void Initialize();
	void Update();
	void Release();
private:
	Player* player;
};

