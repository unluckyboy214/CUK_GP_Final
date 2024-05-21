#include "Monster.h"
#include "globals.h"
#include <SDL_image.h>
#include <cmath>
#include <string>

Monster::Monster(int x, int y) : x(x), y(y), health(1), currentFrame(0), animationTime(0.0f), animationSpeed(0.1f) {
    LoadTextures();
}

Monster::~Monster() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture);
    }
}

void Monster::LoadTextures() {
    std::vector<std::string> frameFiles = {
        "../../Resource/Monster/slime_frame1.png",
        "../../Resource/Monster/slime_frame2.png",
        "../../Resource/Monster/slime_frame3.png",
        "../../Resource/Monster/slime_frame4.png",
        "../../Resource/Monster/slime_frame5.png",
        "../../Resource/Monster/slime_frame6.png",
        "../../Resource/Monster/slime_frame7.png",
    };

    for (const auto& file : frameFiles) {
        SDL_Surface* temp_surface = IMG_Load(file.c_str());
        if (temp_surface) {
            textures.push_back(SDL_CreateTextureFromSurface(g_renderer, temp_surface));
            SDL_FreeSurface(temp_surface);
        }
        else {
            printf("Failed to load monster texture: %s\n", IMG_GetError());
        }
    }
}

void Monster::Update(float deltaTime, const SDL_Rect& playerRect) {
    AdvanceFrame(deltaTime);
    MoveTowardsPlayer(deltaTime, playerRect);
}

void Monster::AdvanceFrame(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= animationSpeed) {
        animationTime = 0.0f;
        currentFrame = (currentFrame + 1) % textures.size();
    }
}

void Monster::MoveTowardsPlayer(float deltaTime, const SDL_Rect& playerRect) {
    float moveSpeed = 100.0f; // Adjust the speed as needed

    float deltaX = playerRect.x - x;
    float deltaY = playerRect.y - y;
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 0) {
        x += static_cast<int>(moveSpeed * deltaX / distance * deltaTime);
        y += static_cast<int>(moveSpeed * deltaY / distance * deltaTime);
    }
}

void Monster::Render() {
    if (!textures.empty()) {
        SDL_Rect rect = { x, y, 128, 128 }; // Render size of 128x128
        SDL_RenderCopy(g_renderer, textures[currentFrame], NULL, &rect);
    }
}

int Monster::getX() const {
    return x;
}

int Monster::getY() const {
    return y;
}

bool Monster::CheckCollisionWithPlayer(const SDL_Rect& playerRect) {
    SDL_Rect monsterRect = { x, y, 128, 128 }; // Adjust collision size to match render size
    return SDL_HasIntersection(&monsterRect, &playerRect);
}
