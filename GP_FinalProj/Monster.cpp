//Monster.cpp
#include "Monster.h"
#include "globals.h"  // Include the globals header
#include <SDL_image.h>
#include <cmath>
#include <iostream>

Monster::Monster(int x, int y) : x(x), y(y), health(2), maxHealth(2), currentFrame(0), animationTime(0.0f), animationSpeed(0.1f) {}

Monster::~Monster() {
    for (auto texture : textures) {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
    textures.clear();
}

void Monster::LoadTextures(const std::vector<std::string>& frameFiles) {
    for (const auto& file : frameFiles) {
        SDL_Surface* temp_surface = IMG_Load(file.c_str());
        if (temp_surface) {
            textures.push_back(SDL_CreateTextureFromSurface(g_renderer, temp_surface));
            SDL_FreeSurface(temp_surface);
        }
        else {
            std::cerr << "Failed to load monster texture: " << IMG_GetError() << std::endl;
        }
    }
}

void Monster::Update(float deltaTime, const SDL_Rect& playerRect) {
    AdvanceFrame(deltaTime);
}

void Monster::AdvanceFrame(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= animationSpeed) {
        animationTime = 0.0f;
        currentFrame = (currentFrame + 1) % textures.size();
    }
}

void Monster::RenderHealthBar() {
    if (health < maxHealth) {
        int barWidth = 50;
        int barHeight = 5;
        int barX = x + (128 - barWidth) / 2;  // 체력 바 x 좌표 계산
        int barY = y - 10;  // 체력 바 y 좌표 계산

        // 체력 바 배경 렌더링
        SDL_Rect backgroundRect = { barX, barY, barWidth, barHeight };
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);  // 빨간색
        SDL_RenderFillRect(g_renderer, &backgroundRect);

        // 현재 체력 바 렌더링
        int healthWidth = (health * barWidth) / maxHealth;
        SDL_Rect healthRect = { barX, barY, healthWidth, barHeight };
        SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);  // 초록색
        SDL_RenderFillRect(g_renderer, &healthRect);
    }
}

void Monster::Render() {
    if (!textures.empty()) {
        SDL_Rect rect = { x, y, 128, 128 };
        SDL_RenderCopy(g_renderer, textures[currentFrame], NULL, &rect);
        RenderHealthBar();  // 체력 바 렌더링 추가
    }
}

bool Monster::CheckCollisionWithPlayer(const SDL_Rect& playerRect) {
    SDL_Rect monsterRect = GetRect(); // 몬스터의 충돌 범위를 가져옴
    return SDL_HasIntersection(&monsterRect, &playerRect);
}

int Monster::getX() const {
    return x;
}

int Monster::getY() const {
    return y;
}

void Monster::SetHealth(int newHealth) {
    health = newHealth;
}

bool Monster::IsDead() const {
    return health <= 0;
}

int Monster::GetHealth() const {
    return health;
}

SDL_Rect Monster::GetRect() const {
    return { x, y, 128, 128 }; // 충돌 범위의 크기를 렌더링 크기와 일치시킴
}
