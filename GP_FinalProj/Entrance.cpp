#include "Entrance.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include <SDL_image.h>
#include <random>

Entrance::Entrance()
    : Map("../../Resource/Map/Entrance.png", 4) {  // maxMonsters 설정
    spawnDelay = 1.0f;  // 초기 몬스터 생성 지연 시간 설정
}

void Entrance::SpawnMonsters() {
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
        int x, y;
        generatePosition(x, y);
        monsters.push_back(new MovingMonster(x, y));
    }
}

void Entrance::SpawnMonster() {
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
        if (monsters.size() % 2 == 0) {
            monsters.push_back(new MovingMonster(x, y));
        }
    }
}

