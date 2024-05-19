#include "RandomMovingMonster.h"
#include <cstdlib>

RandomMovingMonster::RandomMovingMonster(int x, int y) : Monster(x, y) {}

void RandomMovingMonster::Update(int playerX, int playerY) {
    // 임의의 방향으로 움직임
    int direction = rand() % 4;
    switch (direction) {
    case 0: x++; break; // 오른쪽
    case 1: x--; break; // 왼쪽
    case 2: y++; break; // 아래쪽
    case 3: y--; break; // 위쪽
    }
}
