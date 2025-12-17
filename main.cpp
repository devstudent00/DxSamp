#include "DxLib.h"
#include "global.h"
#include "input.h"
#include <vector>
#include "Player.h"

namespace
{
	const int BGCOLOR[3] = { 255, 250, 205 }; // 背景色{ 255, 250, 205 }; // 背景色
	int crrTime;
	int prevTime;

	int SKY_COLOR[3] = { 178, 237, 232 };
	int GREEN_ZONE = 50;
	int GREEN_COLOR = GetColor(50, 205, 50);

	Player* player = nullptr;
}


float gDeltaTime = 0.0f; // フレーム間の時間差

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0], BGCOLOR[1], BGCOLOR[2]);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void Initialize()
{

	//const Vector2D& pos, const Vector2D& vel, const Vector2D& dire, float radius, float omega, float angles, unsigned int color, SHAPE shape)
	//const Vector2D& dire, float radius, float omega, float angles, unsigned int color, SHAPE shape)
	player = new Player({ 600,600 }, { 0,0 }, {0, -1}, 60.0f, 1.0f, 0.0f, GetColor(255, 0, 0), SHAPE::CIRLCE);
	
}
void Update()
{
	player->Update();
}

void Draw()
{
	player->Draw();
}

void DrawStage() {
	SetBackgroundColor(SKY_COLOR[0], SKY_COLOR[1], SKY_COLOR[2]);
}

void Release() {

}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();

	Initialize();

	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate(); // キー入力の状態を更新

		crrTime = GetNowCount(); // 現在の時間を取得
		// 前回の時間との差分を計算
		float deltaTime = (crrTime - prevTime) / 1000.0f; // 秒単位に変換
		gDeltaTime = deltaTime; // グローバル変数に保存

		//ここにやりたい処理を書く
		Update();

		Draw();
		DrawStage();

		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime; // 現在の時間を前回の時間として保存

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	Release();
	DxLib_End();
	return 0;
}