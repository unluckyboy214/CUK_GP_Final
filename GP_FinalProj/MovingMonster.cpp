#include "MovingMonster.h"
#include "globals.h"
#include <cmath>

MovingMonster::MovingMonster(int x, int y) : Monster(x, y), health(3), isStunned(false) { // Initial health set to 3
    normalFrameFiles = {
        "../../Resource/Monster/slime_frame1.png",
        "../../Resource/Monster/slime_frame2.png",
        "../../Resource/Monster/slime_frame3.png",
        "../../Resource/Monster/slime_frame4.png",
        "../../Resource/Monster/slime_frame5.png"
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

void MovingMonster::MoveTowardsPlayer(float deltaTime, const SDL_Rect& playerRect) {
    float moveSpeed = 50.0f; // Adjust the speed as needed

    float deltaX = playerRect.x - x;
    float deltaY = playerRect.y - y;
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 0) {
        x += static_cast<int>(moveSpeed * deltaX / distance * deltaTime);
        y += static_cast<int>(moveSpeed * deltaY / distance * deltaTime);
    }

    // Update facing direction
    facingRight = deltaX <= 0;
}

void MovingMonster::Render() {
    if (!textures.empty()) {
        SDL_Rect rect = { x, y, 128, 128 };

        // Apply hit effect
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - hitStartTime < hitTimer * 1000) {
            // Alternate color for flashing effect
            if (static_cast<int>((currentTime - hitStartTime) / 100) % 2 == 0) {
                SDL_SetTextureColorMod(textures[currentFrame], 255, 0, 0); // Red
            }
            else {
                SDL_SetTextureColorMod(textures[currentFrame], 255, 255, 255); // Original color
            }
        }
        else {
            SDL_SetTextureColorMod(textures[currentFrame], 255, 255, 255); // Original color
        }

        SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(g_renderer, textures[currentFrame], NULL, &rect, 0, NULL, flip);

        RenderHealthBar();
    }
}
