#include "Monster.h"
#include "globals.h"  // Include the globals header
#include <SDL_image.h>
#include <cmath>
#include <iostream>

Monster::Monster(int x, int y) : x(x), y(y), health(1), currentFrame(0), animationTime(0.0f), animationSpeed(0.1f) {}

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

void Monster::Render() {
    if (!textures.empty()) {
        SDL_Rect rect = { x, y, 128, 128 }; // Render size of 128x128
        SDL_RenderCopy(g_renderer, textures[currentFrame], NULL, &rect);
    }
}

bool Monster::CheckCollisionWithPlayer(const SDL_Rect& playerRect) {
    SDL_Rect monsterRect = { x, y, 128, 128 }; // Adjust collision size to match render size
    return SDL_HasIntersection(&monsterRect, &playerRect);
}

int Monster::getX() const {
    return x;
}

int Monster::getY() const {
    return y;
}
