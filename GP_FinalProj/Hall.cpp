#include "GameClass.h"
#include "Hall.h"
#include "ChargingMonster.h"
#include <SDL_image.h>
#include <random>

Hall::Hall()
    : Map("../../Resource/Map/Hall.png", { (WINDOW_WIDTH - 100) / 2, 0, 100, 100 }) {
    SpawnMonsters(); // 여기서 SpawnMonsters를 호출합니다.
}

void Hall::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    for (int i = 0; i < 3; ++i) { // Create 3 charging monsters
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new ChargingMonster(x, y));
    }
}
