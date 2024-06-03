#include "Hall.h"
#include <random>
#include <SDL_image.h>

Hall::Hall() : Map("../../Resource/Map/Hall.png",10) {
    SpawnMonsters();
}

void Hall::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    const int minDistanceFromPlayer = 200; // 플레이어로부터 최소 거리

    auto generatePosition = [&](int& x, int& y) {
        do {
            x = disX(gen);
            y = disY(gen);
        } while (std::sqrt(std::pow(player_.GetRect().x - x, 2) + std::pow(player_.GetRect().y - y, 2)) < minDistanceFromPlayer);
    };



    for (int i = 0; i < 4; ++i) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new ChargingMonster(x, y));
    }

}

void Hall::SpawnMonster() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);
    const int minDistanceFromPlayer = 200; // 플레이어로부터 최소 거리

    auto generatePosition = [&](int& x, int& y) {
        do {
            x = disX(gen);
            y = disY(gen);
        } while (std::sqrt(std::pow(player_.GetRect().x - x, 2) + std::pow(player_.GetRect().y - y, 2)) < minDistanceFromPlayer);
    };

    if (monsters.size() < maxMonsters) {

        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new ChargingMonster(x, y));
    }


}
