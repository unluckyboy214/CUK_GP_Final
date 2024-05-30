// K_Npc.cpp
#include "K_Npc.h"
#include <SDL_image.h>

K_Npc::K_Npc(const char* texturePath, int x, int y, int width, int height, SDL_Renderer* renderer) {
    m_rect = { x, y, width, height };
    SDL_Surface* surface = IMG_Load(texturePath);
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    scriptWindow_ = new ScriptWindow();
    isInteracting_ = false;
}

K_Npc::~K_Npc() {
    SDL_DestroyTexture(m_texture);
    delete scriptWindow_;
}

void K_Npc::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
    if (IsInteracting()) {
        scriptWindow_->Render();
    }
}

bool K_Npc::CheckCollision(const SDL_Rect& playerRect) {
    return SDL_HasIntersection(&m_rect, &playerRect);
}

void K_Npc::StartInteraction() {
    isInteracting_ = true;
    scriptWindow_->Show();
}

bool K_Npc::IsInteracting() {
    return isInteracting_;
}