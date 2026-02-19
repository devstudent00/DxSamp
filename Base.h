#pragma once
#include "Math2D.h"
#include <string>

enum ObjType {

};

class Base
{
public:
	Base();
	Base(const Vector2D& pos, const Vector2D& vel, unsigned int color);
	virtual ~Base() = default;
	virtual void Update(); //オーバーライドしそう
	virtual void Draw(); //オーバーライドしそう
public:
	bool isAlive_;
	//セッター、ゲッター　インライン定義
	void SetPos(const Vector2D& pos) { pos_ = pos; }
	Vector2D GetPos() const { return pos_; }
	void SetVel(const Vector2D& vel) { vel_ = vel; }
	Vector2D GetVel() const { return vel_; }
	void GetCharaColor(const unsigned int color) { Color_ = color; }
	unsigned int GetCharaColor() const { return Color_; };
	bool IsAlive() const { return isAlive_; }
	
protected:
	
	Vector2D pos_;//位置
	Vector2D vel_;//速度
	unsigned int Color_;//色 符号なし整数
	std::string objName_;
	ObjType type_;
};

