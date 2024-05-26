#include "MovingMonster.h"
#include "globals.h"
#include <cmath>

MovingMonster::MovingMonster(int x, int y) : Monster(x, y) {
    std::vector<std::string> frameFiles = {
        "../../Resource/Monster/slime_frame1.png",
        "../../Resource/Monster/slime_frame2.png",
        "../../Resource/Monster/slime_frame3.png",
        "../../Resource/Monster/slime_frame4.png",
        "../../Resource/Monster/slime_frame5.png",
        "../../Resource/Monster/slime_frame6.png",
        "../../Resource/Monster/slime_frame7.png",
    };
    LoadTextures(frameFiles);
}

void MovingMonster::Update(float deltaTime, const SDL_Rect& playerRect) {
    AdvanceFrame(deltaTime);
    MoveTowardsPlayer(deltaTime, playerRect);
}

void MovingMonster::MoveTowardsPlayer(float deltaTime, const SDL_Rect& playerRect) {
    float moveSpeed = 100.0f; // Adjust the speed as needed

    float deltaX = playerRect.x - x;
    float deltaY = playerRect.y - y;
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 0) {
        x += static_cast<int>(moveSpeed * deltaX / distance * deltaTime);
        y += static_cast<int>(moveSpeed * deltaY / distance * deltaTime);
    }
}

void MovingMonster::ParryEffect(const SDL_Rect& playerRect) {
    float knockbackSpeed = 50.0f; // Adjust the knockback speed as needed

    float deltaX = x - playerRect.x;
    float deltaY = y - playerRect.y;
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 0) {
        x += static_cast<int>(knockbackSpeed * deltaX / distance);
        y += static_cast<int>(knockbackSpeed * deltaY / distance);
    }
}
