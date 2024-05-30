// K_Npc.cpp
#include "K_Npc.h"
#include <SDL_image.h>

K_Npc::K_Npc(const char* texturePath, int x, int y, int width, int height, SDL_Renderer* renderer) {
    m_rect = { x, y, width, height };
    SDL_Surface* surface = IMG_Load(texturePath);
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void K_Npc::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
}

bool K_Npc::CheckCollision(const SDL_Rect& playerRect) {
    return SDL_HasIntersection(&m_rect, &playerRect);
}