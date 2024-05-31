// Button.cpp
#include "Button.h"
#include "GameClass.h"
#include <SDL_image.h>

Button::Button(int x, int y, int width, int height, const char* imagePath)
    : rect_{ x, y, width, height }, texture_(nullptr) {
    SDL_Surface* surface = IMG_Load('../../Resource/Script/Button.png');
    texture_ = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_FreeSurface(surface);
}

Button::~Button() {
    SDL_DestroyTexture(texture_);
}

void Button::Render() {
    SDL_RenderCopy(g_renderer, texture_, NULL, &rect_);
}

bool Button::IsClicked(int mouseX, int mouseY) {
    return mouseX >= rect_.x && mouseX <= rect_.x + rect_.w &&
        mouseY >= rect_.y && mouseY <= rect_.y + rect_.h;
}