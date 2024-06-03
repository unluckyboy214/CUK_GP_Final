#include "Entrance.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include <SDL_image.h>
#include <random>

Entrance::Entrance()
    : Map("../../Resource/Map/Entrance.png", 7) {  // maxMonsters 설정
    spawnDelay = 1.0f;  // 초기 몬스터 생성 지연 시간 설정
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

void Entrance::SpawnMonster() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    if (monsters.size() < maxMonsters) {
        int x = disX(gen);
        int y = disY(gen);
        if (monsters.size() % 2 == 0) {
            monsters.push_back(new MovingMonster(x, y));
        }
        else {
            monsters.push_back(new RangedMonster(x, y));
        }
    }
}
