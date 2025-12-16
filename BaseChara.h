#pragma once
#include "Vector2D.h"

//形状
//0:円 1:正方形 2:長方形　3:三角形

//const int SHAPE_CIRCLE = 0;
//const int SHAPE_SQUARE = 1;
//const int SHAPE_RECTANGLE = 2;
//const int SHAPE_TRIANGLE = 3;
//enum : 列挙子　整数の番号を自動でつけてくれる謎機能
enum SHAPE
{
	CIRLCE,
	SQUARE,
	RECTANGLE,
	TRIANGLE
};

class BaseChara
{
public:
	BaseChara();
	BaseChara(const Vector2D& pos,const Vector2D& vel, 
		       unsigned int color, SHAPE shape);
	~BaseChara();
	virtual void Update(); //オーバーライドしそう
	virtual void Draw(); //オーバーライドしそう
public:
	//セッター、ゲッター　インライン定義
	void SetPos(const Vector2D& pos) { pos_ = pos; }
	Vector2D GetPos() const { return pos_; }
	void SetVel(const Vector2D& vel) { vel_ = vel; }
	Vector2D GetVel() const { return vel_; }
	void GetCharaColor(const unsigned int color) { Color_ = color; }
	unsigned int GetCharaColor() const { return Color_; }
	void SetShape(const int shape) { shape_ = shape; }
	int GetShape() const { return shape_; }
private:
	unsigned int Color_;//色 符号なし整数
	int shape_;//形状
protected:
	Vector2D pos_;//位置
	Vector2D vel_;//速度
};

