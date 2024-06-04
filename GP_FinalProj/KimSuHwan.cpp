#include "KimSuHwan.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include "ChargingMonster.h"
#include <SDL_image.h>
#include <random>

KimSuHwan::KimSuHwan() : Map("../../Resource/Map/KimSuHwan.png",4) {
    SpawnMonsters(); // SpawnMonsters 호출
}

void KimSuHwan::SpawnMonsters() {
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

    /*for (int i = 0; i < 0; ++i) {
        int x, y;
        generatePosition(x, y);
        monsters.push_back(new MovingMonster(x, y));
    }
    for (int i = 0; i < 0; ++i) {
        int x, y;
        generatePosition(x, y);
        monsters.push_back(new RangedMonster(x, y));
    }*/
    for (int i = 0; i < 4; ++i) {
        int x, y;
        generatePosition(x, y);
        monsters.push_back(new ChargingMonster(x, y));
    }
}

void KimSuHwan::SpawnMonster() {
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
        int x, y;
        generatePosition(x, y);
        monsters.push_back(new ChargingMonster(x, y));
    }
}
