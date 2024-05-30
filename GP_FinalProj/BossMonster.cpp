#include "BossMonster.h"
#include "globals.h"
#include <SDL_image.h>
#include <cmath>

BossMonster::BossMonster(int x, int y) : Monster(x, y), hp(20) {
    std::vector<std::string> frameFiles = {
        "../../Resource/Monster/boss_frame1.png",
        "../../Resource/Monster/boss_frame2.png"
    };
    LoadTextures(frameFiles);
}

void BossMonster::Update(float deltaTime, const SDL_Rect& playerRect) {
    // 보스 몬스터 업데이트 로직
    // 플레이어를 추적하는 등의 로직 추가 가능
    float moveSpeed = 50.0f;
    float deltaX = playerRect.x - x;
    float deltaY = playerRect.y - y;
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 0) {
        x += static_cast<int>(moveSpeed * deltaX / distance * deltaTime);
        y += static_cast<int>(moveSpeed * deltaY / distance * deltaTime);
    }
}

void BossMonster::Render() {
    Monster::Render();
}

int BossMonster::getHP() const {
    return hp;
}

void BossMonster::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}
