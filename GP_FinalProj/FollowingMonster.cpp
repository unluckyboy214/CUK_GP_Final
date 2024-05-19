#include "FollowingMonster.h"
#include <cmath>

FollowingMonster::FollowingMonster(int x, int y) : Monster(x, y) {}

void FollowingMonster::Update(int playerX, int playerY) {
    // 간단한 추적 알고리즘
    if (playerX > x) x++;
    else if (playerX < x) x--;

    if (playerY > y) y++;
    else if (playerY < y) y--;
}
