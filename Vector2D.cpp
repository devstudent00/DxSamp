#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D(float _x, float _y)
	:x(_x), y(_y) {
}

Vector2D Vector2D::Add(const Vector2D& v_) {
	float newVx = x + v_.x;
	float newVy = y + v_.y;
	return Vector2D{newVx, newVy};
}

Vector2D Vector2D::Subtract(const Vector2D& v_) {
	float newVx = x - v_.x;
	float newVy = y - v_.y;
	return Vector2D{ newVx, newVy };
}

Vector2D Vector2D::ScalarMul(float k) {
	float newVx = k * x;
	float newVy = k * y;
	return Vector2D{ newVx, newVy };
}

Vector2D Vector2D::Zero() {
	return Vector2D{0, 0};
}

float Vector2D::Distance(const Vector2D& v_) {
	float dist2 = (v_.x - x) * (v_.x - x) + (v_.y - y) * (v_.y - y);
	return sqrt(dist2);
}
