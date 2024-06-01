#include "MovingMonster.h"
#include "globals.h"
#include <cmath>

MovingMonster::MovingMonster(int x, int y) : Monster(x, y), health(3), isStunned(false) { // Initial health set to 3
    normalFrameFiles = {
        "../../Resource/Monster/slime_frame1.png",
        "../../Resource/Monster/slime_frame2.png",
        "../../Resource/Monster/slime_frame3.png",
        "../../Resource/Monster/slime_frame4.png",
        "../../Resource/Monster/slime_frame5.png",
        "../../Resource/Monster/slime_frame6.png",
        "../../Resource/Monster/slime_frame7.png",
        "../../Resource/Monster/slime_frame8.png"
    };

    stunFrameFiles = {
        "../../Resource/Monster/slime_stun_frame1.png",
        "../../Resource/Monster/slime_stun_frame2.png",
        "../../Resource/Monster/slime_stun_frame3.png",
        "../../Resource/Monster/slime_stun_frame4.png",
        "../../Resource/Monster/slime_stun_frame5.png",
        "../../Resource/Monster/slime_stun_frame6.png",
        "../../Resource/Monster/slime_stun_frame7.png",
        "../../Resource/Monster/slime_stun_frame8.png"
    };

    LoadTextures(normalFrameFiles);
}

void MovingMonster::Update(float deltaTime, const SDL_Rect& playerRect) {
    AdvanceFrame(deltaTime);
    MoveTowardsPlayer(deltaTime, playerRect);

    if (!isStunned) {
        MoveTowardsPlayer(deltaTime, playerRect);
    }
}

void MovingMonster::TakeDamage(int damage) {
    health -= damage;
    if (health == 1 && !isStunned) {
        isStunned = true;
        LoadTextures(stunFrameFiles);
    }
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
