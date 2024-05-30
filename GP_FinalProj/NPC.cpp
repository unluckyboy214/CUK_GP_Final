// NPC.cpp
#include "NPC.h"
#include "GameClass.h"
#include <SDL_image.h>

NPC::NPC(const char* texturePath, int x, int y, SDL_Renderer* renderer, TTF_Font* font)
    : rect_{ x, y, 64, 64 }, texture_(nullptr), isInteracting_(false), font_(font), scriptWindow_(nullptr) {
    LoadTexture(texturePath, renderer);
    scriptWindow_ = new ScriptWindow();
}

NPC::~NPC() {
    SDL_DestroyTexture(texture_);
    delete scriptWindow_;
}

void NPC::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture_, NULL, &rect_);
    if (IsInteracting()) {
        scriptWindow_->Render();
    }
}

void NPC::LoadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* temp_surface = IMG_Load(path);
    texture_ = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
}

bool NPC::CheckCollision(const SDL_Rect& playerRect) {
    return SDL_HasIntersection(&rect_, &playerRect);
}

void NPC::StartInteraction() {
    scriptWindow_->Show();
}

bool NPC::IsInteracting() {
    return scriptWindow_->IsVisible();
}