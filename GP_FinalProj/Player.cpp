// Player.cpp
#include "GameClass.h"
#include "Player.h"
#include "globals.h"
#include <SDL_image.h>

Player::Player() : is_parrying_(false), move_speed_(500.0f) {
    // 플레이어 텍스처 로드
    SDL_Surface* surface = IMG_Load("../../Resource/Character/Isacc.png");
    texture_ = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_FreeSurface(surface);

    rect_ = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100, 100 };
}

void Player::Update(float deltaTime) {
    if (g_move_left) {
        rect_.x -= move_speed_ * deltaTime;
    }
    if (g_move_right) {
        rect_.x += move_speed_ * deltaTime;
    }
    if (g_move_up) {
        rect_.y -= move_speed_ * deltaTime;
    }
    if (g_move_down) {
        rect_.y += move_speed_ * deltaTime;
    }

    // 화면을 벗어나지 않도록 제한
    rect_.x = std::max(0, std::min(WINDOW_WIDTH - rect_.w, rect_.x));
    rect_.y = std::max(0, std::min(WINDOW_HEIGHT - rect_.h, rect_.y));
}

void Player::Render() {
    SDL_RenderCopy(g_renderer, texture_, NULL, &rect_);
}

void Player::HandleEvents(const SDL_Event& event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            g_move_left = true;
            break;
        case SDLK_RIGHT:
            g_move_right = true;
            break;
        case SDLK_UP:
            g_move_up = true;
            break;
        case SDLK_DOWN:
            g_move_down = true;
            break;
        case SDLK_SPACE:
            SetParrying(true);
            break;
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            g_move_left = false;
            break;
        case SDLK_RIGHT:
            g_move_right = false;
            break;
        case SDLK_UP:
            g_move_up = false;
            break;
        case SDLK_DOWN:
            g_move_down = false;
            break;
        case SDLK_SPACE:
            SetParrying(false);
            break;
        }
        break;
    }
}

void Player::SetParrying(bool parrying) {
    is_parrying_ = parrying;
}

bool Player::IsParrying() const {
    return is_parrying_;
}

const SDL_Rect& Player::GetRect() const {
    return rect_;
}
