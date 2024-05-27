#include "GameClass.h"
#include "KimSuHwan.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include <SDL_image.h>
#include <random>

KimSuHwan::KimSuHwan()
    : Map("../../Resource/Map/KimSuHwan.png", { (WINDOW_WIDTH - 100) / 2, 0, 100, 100 }) {
    SpawnMonsters(); // 여기서 SpawnMonsters를 호출합니다.
}

void KimSuHwan::SpawnMonsters() {
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
