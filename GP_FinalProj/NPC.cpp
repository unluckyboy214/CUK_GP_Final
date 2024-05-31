#include "NPC.h"
#include <SDL_image.h>

NPC::NPC(SDL_Renderer* renderer, const char* imagePath, int x, int y) {
    texture = IMG_LoadTexture(renderer, imagePath);
    rect = { x, y, 0, 0 };
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
}

NPC::~NPC() {
    SDL_DestroyTexture(texture);
}

void NPC::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void NPC::setSize(int width, int height) {
    rect.w = width;
    rect.h = height;
}