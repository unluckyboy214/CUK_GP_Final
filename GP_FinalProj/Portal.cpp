// Portal.cpp
#include "Portal.h"
#include "GameClass.h"
#include <SDL_image.h>

Portal::Portal(int x, int y, int dx, int dy)
    : dx_(dx), dy_(dy) {
    rect_ = { x, y, 100, 100 };

    // 포탈 텍스처 로드
    SDL_Surface* surface = IMG_Load("../../Resource/Map/portal.png");
    texture_ = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_FreeSurface(surface);
}

void Portal::Render() const {
    SDL_RenderCopy(g_renderer, texture_, NULL, &rect_);
}

bool Portal::IsColliding(const SDL_Rect& rect) const {
    return SDL_HasIntersection(&rect_, &rect);
}

int Portal::GetDX() const {
    return dx_;
}

int Portal::GetDY() const {
    return dy_;
}