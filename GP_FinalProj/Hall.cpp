#include "Hall.h"
#include <random>
#include <SDL_image.h>

Hall::Hall() : Map("../../Resource/Map/Hall.png") {
    SpawnMonsters();
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
