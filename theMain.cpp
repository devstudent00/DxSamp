#include "DxLib.h"
#include "NewEnemy.h"
#include "globals.h"
#include "input.h"
#include "Stage.h"
#include "ImGui/imgui_impl_dxlib.hpp"
#include "ObjectManager.h"
#include "Player.h"

namespace
{
	const int BGCOLOR[3] = {0, 0, 51}; // 背景色{ 255, 250, 205 }; // 背景色
	int crrTime;
	int prevTime;

	Stage* stage = nullptr;
	bool DEBUG_MODE = true;

	ObjectManager& objManager = ObjectManager::GetInstance();
}


float gDeltaTime = 0.0f; // フレーム間の時間差

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0],BGCOLOR[1],BGCOLOR[2]);
	SetAlwaysRunFlag(true);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void Initialize()
{
	// 独自の初期化処理をここに記述
	stage = new Stage();
	stage->Initialize();

	SetHookWinProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT /*CALLBACK*/
		{
			// DxLibとImGuiのウィンドウプロシージャを両立させる
			SetUseHookWinProcReturnValue(FALSE);
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		});
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.Fonts->AddFontFromFileTTF(u8"c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	ImGui_ImplDXlib_Init();
}

void Update()
{
	
	// 独自の更新処理をここに記述
	stage->Update();
}
void Draw()
{
	// 独自の描画処理をここに記述
	stage->Draw();
}
void Release()
{
	// 独自の終了処理をここに記述
	stage->Release();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();

	Initialize(); // 独自の初期化処理

	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate(); // キー入力の状態を更新

		crrTime = GetNowCount(); // 現在の時間を取得
		// 前回の時間との差分を計算
		float deltaTime = (crrTime - prevTime) / 1000.0f; // 秒単位に変換
		gDeltaTime = deltaTime; // グローバル変数に保存
		
		//ここにやりたい処理を書く
		Update(); // 独自の更新処理
		Draw(); // 独自の描画処理

		if (DEBUG_MODE) {
			ImGui_ImplDXlib_NewFrame();
			ImGui::NewFrame();

			auto& enemy = objManager.GetGameObjects<NewEnemy>();
			auto player = objManager.GetGameObject<Player>();
			ImGui::Begin("Debug Window");
			ImGui::Text("DeltaTime: %.3f", gDeltaTime);
			ImGui::Text(u8"すべてのオブジェクトの数：%d", objManager.GetAllObjectSize());
			ImGui::Text(u8"敵の数：%d", enemy.size());
			ImGui::Text(u8"敵とプレイヤー当たってる?: %d", player->isHit);
			if (ImGui::Button(u8"敵をスポーン")) stage->SpawnEnemy();			
			
			ImGui::End();

			ImGui::Render();
			ImGui::EndFrame();
			ImGui_ImplDXlib_RenderDrawData();
			RefreshDxLibDirect3DSetting();
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
			}
		}

		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime; // 現在の時間を前回の時間として保存

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	Release(); // 独自の終了処理
	DxLib_End();
	return 0;
}