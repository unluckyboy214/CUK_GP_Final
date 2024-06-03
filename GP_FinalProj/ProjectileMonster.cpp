// ProjectileMonster.cpp
#include "ProjectileMonster.h"
#include "globals.h"
ProjectileMonster::ProjectileMonster(int x, int y, float velX, float velY)
	: Monster(x, y), velX(velX), velY(velY) {
	SetRect(x, y, 16, 16);
}
void ProjectileMonster::Update(float deltaTime) {  // 함수 정의 수정
	SetPosition(getX() + static_cast<int>(velX * deltaTime), getY() + static_cast<int>(velY * deltaTime));
}
bool ProjectileMonster::IsOutOfBounds() const {
	int x = getX();
	int y = getY();
	return (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT);
}