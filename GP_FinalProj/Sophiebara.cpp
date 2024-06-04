#include "Sophiebara.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include "ChargingMonster.h"
#include <SDL_image.h>
#include <random>

Sophiebara::Sophiebara()
    : Map("../../Resource/Map/Sophiebara.png", 7) {  // maxMonsters ����
    spawnDelay = 2.0f;  // �ʱ� ���� ���� ���� �ð� ����
}

void Sophiebara::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    for (int i = 0; i < 3; ++i) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new MovingMonster(x, y));
    }
    for (int i = 0; i < 2; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new RangedMonster(x, y));
    }
    for (int i = 0; i < 2; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new ChargingMonster(x, y));
    }
}

void Sophiebara::SpawnMonster() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    if (monsters.size() < maxMonsters) {
        int x = disX(gen);
        int y = disY(gen);
        deathCount++;
        if (deathCount % 3 == 1) {
            monsters.push_back(new MovingMonster(x, y));
        }
        else if (deathCount % 3 == 2) {
            monsters.push_back(new RangedMonster(x, y));
        }
        else if (deathCount % 3 == 0) {
            monsters.push_back(new ChargingMonster(x, y));
        }
    }
}
