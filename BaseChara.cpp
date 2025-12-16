#include "BaseChara.h"
#include <DxLib.h>
#include "global.h"

BaseChara::BaseChara()
	:pos_(0.0f, 0.0f),
	vel_(0.0f, 0.0f),
	Color_(GetColor(0,0,0)),
	shape_(SHAPE::CIRLCE)
{
}
//メンバイニシャライザでもいいし、コンストラクタ内で代入してもいい
BaseChara::BaseChara(const Vector2D& pos,const  Vector2D& vel, unsigned int color, SHAPE shape)
	:pos_(pos),
	vel_(vel),
	Color_(color),
	shape_(shape)
{}

BaseChara::~BaseChara()
{
	//デストラクタ（何もしない）
}

void BaseChara::Update()
{
	//何もしない
}

void BaseChara::Draw() {
	//これは呼ばれてしまった分かりやすいものを書いておく
	int centerX = WIN_WIDTH / 2;
	int centerY = WIN_HEIGHT / 2;
	int beforeSize = GetFontSize();
	SetFontSize(50);
	DrawString(centerX, centerY, "BaseCharaDraw()", GetColor(255, 0, 0));
	SetFontSize(beforeSize);
}
