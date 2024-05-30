// Player.cpp
#include "GameClass.h"
#include "Player.h"
#include "globals.h"
#include <SDL_image.h>
#include <iostream>

Player::Player() : is_parrying_(false), move_speed_(500.0f), parry_cooldown_(0.5f), parry_duration_(0.1f), parry_timer_(0.0f), direction_(0) {
    // 플레이어 텍스처 로드
    SDL_Surface* surface = IMG_Load("../../Resource/Character/Isacc.png");
    texture_ = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_FreeSurface(surface);

    rect_ = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100, 100 };
}

void Player::Update(float deltaTime) {
    if (g_move_left) {
        rect_.x -= move_speed_ * deltaTime;
        direction_ = 3; // 왼쪽
    }
    if (g_move_right) {
        rect_.x += move_speed_ * deltaTime;
        direction_ = 1; // 오른쪽
    }
    if (g_move_up) {
        rect_.y -= move_speed_ * deltaTime;
        direction_ = 0; // 위
    }
    if (g_move_down) {
        rect_.y += move_speed_ * deltaTime;
        direction_ = 2; // 아래
    }

    // 패링 타이머 업데이트
    if (parry_timer_ > 0) {
        parry_timer_ -= deltaTime;
    }
    else {
        is_parrying_ = false;
    }

    // 화면을 벗어나지 않도록 제한
    rect_.x = std::max(0, std::min(WINDOW_WIDTH - rect_.w, rect_.x));
    rect_.y = std::max(0, std::min(WINDOW_HEIGHT - rect_.h, rect_.y));
}
void Player::Render() {
    if (is_parrying_) {
        // 패링 상태일 때 다른 색상으로 렌더링
        SDL_SetTextureColorMod(texture_, 255, 0, 0); // 빨간색으로 변경
        SDL_RenderCopy(g_renderer, texture_, NULL, &rect_);
        SDL_SetTextureColorMod(texture_, 255, 255, 255); // 원래 색상으로 복원
    }
    else {
        SDL_RenderCopy(g_renderer, texture_, NULL, &rect_);
    }
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
            PerformParry();
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
        }
        break;
    }
}


void Player::PerformParry() {
    if (parry_timer_ <= 0) {
        is_parrying_ = true;
        parry_timer_ = parry_cooldown_ + parry_duration_;
        float parry_distance = 10.0f; // 패링 시 이동 거리

        switch (direction_) {
        case 0: rect_.y -= parry_distance; break; // 위
        case 1: rect_.x += parry_distance; break; // 오른쪽
        case 2: rect_.y += parry_distance; break; // 아래
        case 3: rect_.x -= parry_distance; break; // 왼쪽
        }
    }
}

void Player::SetParrying(bool parrying) {
    is_parrying_ = parrying;
}

bool Player::IsParrying() const {
    return is_parrying_;
}

const SDL_Rect& Player::GetRect() const {
    return rect_; // 플레이어의 위치를 나타내는 SDL_Rect 객체의 참조 반환
}