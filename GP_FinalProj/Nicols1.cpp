#include "Nicols1.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include <SDL_image.h>
#include <random>

Nicols1::Nicols1()
    : Map("../../Resource/Map/Nicols1.png", 5) {  // maxMonsters 설정
    spawnDelay = 2.0f;  // 초기 몬스터 생성 지연 시간 설정
}

void Nicols1::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    for (int i = 0; i < 4; ++i) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new MovingMonster(x, y));
    }
    for (int i = 0; i < 1; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new RangedMonster(x, y));
    }
}

void Nicols1::SpawnMonster() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    if (monsters.size() < maxMonsters) {
        int x = disX(gen);
        int y = disY(gen);
        deathCount++;
        if (deathCount % 3 == 0) {
            monsters.push_back(new RangedMonster(x, y));
        }
        else {
            monsters.push_back(new MovingMonster(x, y));
        }
    }
}
