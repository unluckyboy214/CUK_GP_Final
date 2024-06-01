#include "Entrance.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include <SDL_image.h>
#include <random>

Entrance::Entrance()
    : Map("../../Resource/Map/Entrance.png") {
    // 스테이지 초기 시작 시에는 몬스터를 생성하지 않음
    spawnDelay = 10.0f;  // 첫 스테이지에서의 초기 지연 시간 설정
}

void Entrance::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    for (int i = 0; i < 4; ++i) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new MovingMonster(x, y));
    }
    for (int i = 0; i < 3; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new RangedMonster(x, y));
    }
}
