#include "Player.h"
#include "globals.h"
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <algorithm>

bool Player::textures_loaded_ = false;  // 플래그 초기화
std::unordered_map<PlayerState, Animation> Player::shared_animations_;  // 공유 애니메이션 초기화

Player::Player()
    : is_parrying_(false),
    move_speed_(500.0f),
    parry_cooldown_(0.5f),
    parry_duration_(0.1f),
    parry_timer_(0.0f),
    direction_(0),
    state_(PlayerState::Idle),
    prev_state_(PlayerState::Idle),  // 초기 이전 상태
    current_frame_(0),
    frame_time_(0.0f) {
    if (!textures_loaded_) {
        LoadTextures();
        textures_loaded_ = true;
    }
    animations_ = shared_animations_;
    rect_ = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100, 100 };
}

void Player::LoadTextures() {
    LoadAnimation(PlayerState::Idle, "../../Resource/Character/player/Idle_", 8, 0.1f);
    LoadAnimation(PlayerState::Move, "../../Resource/Character/player/Move_", 5, 0.1f);
    LoadAnimation(PlayerState::Parry, "../../Resource/Character/player/Parry_", 6, 0.1f);
    LoadAnimation(PlayerState::Damage, "../../Resource/Character/player/Damage_", 8, 0.1f);
    LoadAnimation(PlayerState::Death, "../../Resource/Character/player/Death_", 6, 0.1f);
}

void Player::LoadAnimation(PlayerState state, const std::string& base_path, int frame_count, float frame_duration) {
    Animation animation;
    animation.frame_duration = frame_duration;
    for (int i = 1; i <= frame_count; ++i) {
        std::string path = base_path + std::to_string(i) + ".png";
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface) {
            std::cerr << "Failed to load surface: " << path << " Error: " << IMG_GetError() << std::endl;
            continue;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
        SDL_FreeSurface(surface);
        if (!texture) {
            std::cerr << "Failed to create texture: " << path << " Error: " << SDL_GetError() << std::endl;
            continue;
        }
        animation.frames.push_back(texture);
    }
    if (animation.frames.empty()) {
        std::cerr << "No frames loaded for state: " << static_cast<int>(state) << std::endl;
    }
    else {
        std::cout << "Loaded " << animation.frames.size() << " frames for state: " << static_cast<int>(state) << std::endl;
    }
    shared_animations_[state] = animation;
}

void Player::Update(float deltaTime) {
    bool isMoving = false;

    // Handle movement input
    if (g_move_left) {
        rect_.x -= move_speed_ * deltaTime;
        direction_ = 3; // left
        isMoving = true;
    }
    if (g_move_right) {
        rect_.x += move_speed_ * deltaTime;
        direction_ = 1; // right
        isMoving = true;
    }
    if (g_move_up) {
        rect_.y -= move_speed_ * deltaTime;
        direction_ = 0; // up
        isMoving = true;
    }
    if (g_move_down) {
        rect_.y += move_speed_ * deltaTime;
        direction_ = 2; // down
        isMoving = true;
    }

    // Update state based on movement and parrying
    if (is_parrying_) {
        state_ = PlayerState::Parry;
    }
    else if (isMoving) {
        state_ = PlayerState::Move;
    }
    else {
        state_ = PlayerState::Idle;
    }

    // 상태가 변경되면 current_frame을 0으로 초기화
    if (state_ != prev_state_) {
        current_frame_ = 0;
        prev_state_ = state_;
    }

    // Update frame
    frame_time_ += deltaTime;
    if (!animations_[state_].frames.empty() && frame_time_ >= animations_[state_].frame_duration) {
        frame_time_ = 0.0f;
        current_frame_ = (current_frame_ + 1) % animations_[state_].frames.size();
    }

    // Update parry timer
    if (parry_timer_ > 0) {
        parry_timer_ -= deltaTime;
    }
    else {
        is_parrying_ = false;
    }

    // Keep player within window bounds
    rect_.x = std::max(0, std::min(WINDOW_WIDTH - rect_.w, rect_.x));
    rect_.y = std::max(0, std::min(WINDOW_HEIGHT - rect_.h, rect_.y));
}

void Player::Render() {
    // Get current texture based on state and frame
    if (animations_.find(state_) == animations_.end() || animations_[state_].frames.empty()) {
        std::cerr << "Error: no frames available for state " << static_cast<int>(state_) << std::endl;
        return;
    }

    // Validate current frame index
    if (current_frame_ >= animations_[state_].frames.size()) {
        std::cerr << "Error: current_frame_ " << current_frame_ << " is out of bounds for state " << static_cast<int>(state_) << std::endl;
        return;
    }

    SDL_Texture* current_texture = animations_[state_].frames[current_frame_];

    // Render texture if valid
    if (current_texture == nullptr) {
        std::cerr << "Error: current_texture is nullptr in state " << static_cast<int>(state_) << ", frame " << current_frame_ << std::endl;
        return;
    }

    SDL_RenderCopy(g_renderer, current_texture, NULL, &rect_);
}

void Player::HandleEvents(const SDL_Event& event, const std::vector<Monster*>& monsters) {
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
            PerformParry(monsters); // Call PerformParry with monster list
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

void Player::PerformParry(const std::vector<Monster*>& monsters) {
    if (parry_timer_ <= 0) {
        bool monsterInRange = false;
        float parryDistance = 1000.0f; // Parry range
        for (const auto& monster : monsters) {
            int deltaX = monster->getX() - rect_.x;
            int deltaY = monster->getY() - rect_.y;
            float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
            if (distance <= parryDistance) {
                monsterInRange = true;
                break;
            }
        }

        if (monsterInRange) {
            is_parrying_ = true;
            parry_timer_ = parry_cooldown_ + parry_duration_;
            float parry_distance = 100.0f; // Distance to move when parrying

            switch (direction_) {
            case 0: rect_.y -= parry_distance; break; // up
            case 1: rect_.x += parry_distance; break; // right
            case 2: rect_.y += parry_distance; break; // down
            case 3: rect_.x -= parry_distance; break; // left
            }
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
    return rect_;
}

void Player::SetPosition(int x, int y) {
    rect_.x = x;
    rect_.y = y;
}
