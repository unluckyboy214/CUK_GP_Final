#include "StaticMonster.h"

StaticMonster::StaticMonster(int x, int y) : Monster(x, y) {}

void StaticMonster::Update(int playerX, int playerY) {
    // StaticMonster는 위치를 업데이트하지 않습니다.
}
