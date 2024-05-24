#include "Health.h"
#include "globals.h"
#include <iostream>

Health::Health(SDL_Renderer* renderer) : renderer(renderer) {
    for (int i = 0; i < g_player_health; ++i) {
        heartTextures.push_back(LoadTexture("../../Resource/Character/heart.png"));
    }
}

Health::~Health() {
    for (auto texture : heartTextures) {
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture* Health::LoadTexture(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load surface: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }
    return texture;
}

void Health::Render() {
    int heartWidth = 32;
    int heartHeight = 32;
    for (int i = 0; i < g_player_health; ++i) {
        SDL_Rect dstRect = { WINDOW_WIDTH - (i + 1) * (heartWidth + 5), 10, heartWidth, heartHeight };
        SDL_RenderCopy(renderer, heartTextures[i], NULL, &dstRect);
    }
}

void Health::Update(int health) {
    // Update heart textures based on health
    while (heartTextures.size() > health) {
        SDL_DestroyTexture(heartTextures.back());
        heartTextures.pop_back();
    }
    while (heartTextures.size() < health) {
        heartTextures.push_back(LoadTexture("../../Resource/Character/heart.png"));
    }
}
