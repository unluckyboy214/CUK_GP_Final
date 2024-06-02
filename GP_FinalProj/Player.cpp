//Player.cpp
#include "Player.h"
#include "globals.h"
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include "MovingMonster.h"
#include "RangedMonster.h"

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
    frame_time_(0.0f),
    flip_(false),
    dashEffectFrame(0),
    dashEffectTimer(0.0f),
    isDashEffectActive(false),
    velocity_({ 0.0f, 0.0f }),
    dashEffectPosition_({ 0, 0, static_cast<int>(127 * 1.5), static_cast<int>(20 * 1.5) }),
    dashEffectAngle_(0.0) {  // 속도 초기화 및 대시 이펙트 위치 초기화
    if (!textures_loaded_) {
        LoadTextures();
        textures_loaded_ = true;
    }
    animations_ = shared_animations_;
    rect_ = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 150, 150 }; // 캐릭터 크기 조정
    LoadDashEffectTextures();
}

void Player::LoadDashEffectTextures() {
    std::vector<std::string> frameFiles = {
        "../../Resource/Character/effect/effect1.png",
        "../../Resource/Character/effect/effect2.png",
        "../../Resource/Character/effect/effect3.png",
        "../../Resource/Character/effect/effect4.png",
        "../../Resource/Character/effect/effect3.png",
        "../../Resource/Character/effect/effect4.png"
    };

    for (const auto& file : frameFiles) {
        SDL_Surface* temp_surface = IMG_Load(file.c_str());
        if (temp_surface) {
            dashEffectTextures.push_back(SDL_CreateTextureFromSurface(g_renderer, temp_surface));
            SDL_FreeSurface(temp_surface);
        }
        else {
            std::cerr << "Failed to load dash effect texture: " << IMG_GetError() << std::endl;
        }
    }
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
    float acceleration = 3000.0f;  // 가속도
    float deceleration = 3000.0f;  // 감속도
    float maxSpeed = 500.0f;  // 최대 속도
    bool isMoving = false;

    // Handle movement input with acceleration
    if (g_move_left) {
        velocity_.x -= acceleration * deltaTime;
        if (velocity_.x < -maxSpeed) velocity_.x = -maxSpeed;
        direction_ = 3; // left
        isMoving = true;
        flip_ = false;
    }
    if (g_move_right) {
        velocity_.x += acceleration * deltaTime;
        if (velocity_.x > maxSpeed) velocity_.x = maxSpeed;
        direction_ = 1; // right
        isMoving = true;
        flip_ = true;
    }
    if (g_move_up) {
        velocity_.y -= acceleration * deltaTime;
        if (velocity_.y < -maxSpeed) velocity_.y = -maxSpeed;
        direction_ = 0; // up
        isMoving = true;
    }
    if (g_move_down) {
        velocity_.y += acceleration * deltaTime;
        if (velocity_.y > maxSpeed) velocity_.y = maxSpeed;
        direction_ = 2; // down
        isMoving = true;
    }

    // Decelerate when no input is given
    if (!g_move_left && !g_move_right) {
        if (velocity_.x > 0) {
            velocity_.x -= deceleration * deltaTime;
            if (velocity_.x < 0) velocity_.x = 0;
        }
        else if (velocity_.x < 0) {
            velocity_.x += deceleration * deltaTime;
            if (velocity_.x > 0) velocity_.x = 0;
        }
    }

    if (!g_move_up && !g_move_down) {
        if (velocity_.y > 0) {
            velocity_.y -= deceleration * deltaTime;
            if (velocity_.y < 0) velocity_.y = 0;
        }
        else if (velocity_.y < 0) {
            velocity_.y += deceleration * deltaTime;
            if (velocity_.y > 0) velocity_.y = 0;
        }
    }

    // Update player position
    rect_.x += velocity_.x * deltaTime;
    rect_.y += velocity_.y * deltaTime;

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

    UpdateDashEffect(deltaTime);
}

void Player::UpdateDashEffect(float deltaTime) {
    if (isDashEffectActive) {
        dashEffectTimer += deltaTime;
        if (dashEffectTimer >= 0.05f) { // 이펙트 프레임 전환 속도 조절
            dashEffectTimer = 0.0f;
            dashEffectFrame++;
            if (dashEffectFrame >= dashEffectTextures.size()) {
                dashEffectFrame = 0;
                isDashEffectActive = false;
            }
        }
    }
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

    SDL_RendererFlip flip = flip_ ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(g_renderer, current_texture, NULL, &rect_, 0, NULL, flip);

    RenderDashEffect(); // 대시 이펙트 렌더링 호출 추가
}

void Player::RenderDashEffect() {
    if (isDashEffectActive && !dashEffectTextures.empty()) {
        SDL_Rect effectRect = dashEffectPosition_; // 이펙트 위치를 고정된 위치로 설정
        SDL_RenderCopyEx(g_renderer, dashEffectTextures[dashEffectFrame], NULL, &effectRect, dashEffectAngle_, NULL, SDL_FLIP_NONE);
    }
}

void Player::HandleEvents(const SDL_Event& event, std::vector<Monster*>& monsters) {
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

void Player::PerformParry(std::vector<Monster*>& monsters) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    if (parry_timer_ <= 0) {
        is_parrying_ = true;
        float parry_distance = 100.0f; // 패링 시 이동 거리

        isDashEffectActive = true; // 패링 시 이펙트 활성화
        dashEffectFrame = 0;
        dashEffectTimer = 0.0f;

        // 대시 이펙트 위치 및 회전 각도 설정
        dashEffectPosition_ = {
            static_cast<int>(rect_.x + rect_.w / 2 - (127 * 1.5) / 2),
            static_cast<int>(rect_.y + rect_.h / 2 - (20 * 1.5) / 2),
            static_cast<int>(127 * 1.5),
            static_cast<int>(20 * 1.5)
        };
        dashEffectAngle_ = (direction_ == 0 || direction_ == 2) ? 90.0 : 0.0;

        SDL_Rect dashArea = rect_;

        // 대쉬 거리 설정 및 대쉬 영역 계산
        switch (direction_) {
        case 0: // 위
            dashArea.y -= parry_distance;
            dashArea.h = parry_distance;
            break;
        case 1: // 오른쪽
            dashArea.x += rect_.w;
            dashArea.w = parry_distance;
            break;
        case 2: // 아래
            dashArea.y += rect_.h;
            dashArea.h = parry_distance;
            break;
        case 3: // 왼쪽
            dashArea.x -= parry_distance;
            dashArea.w = parry_distance;
            break;
        }

        bool parrySuccess = false; // 패링 성공 여부

        // 대쉬 범위 내의 모든 몬스터를 찾음
        for (auto it = monsters.begin(); it != monsters.end();) {
            SDL_Rect monsterRect = (*it)->GetRect();
            if (SDL_HasIntersection(&dashArea, &monsterRect)) {
                parrySuccess = true; // 패링 성공
                int currentHealth = (*it)->GetHealth();
                (*it)->SetHealth(currentHealth - 1);
                (*it)->SetHitTimer(1.5f); // hitTimer 설정 함수 호출
                std::cout << "Monster at (" << (*it)->getX() << ", " << (*it)->getY() << ") hit, health: " << (*it)->GetHealth() << std::endl; // 디버깅 메시지
                if ((*it)->IsDead()) {
                    delete* it;
                    it = monsters.erase(it);
                    g_kill_count++; // 몬스터 삭제 시 킬 수 증가
                }
                else {
                    ++it;
                }
            }
            else {
                ++it;
            }
        }

        // 패링 성공 여부에 따라 타이머 설정
        if (parrySuccess) {
            parry_timer_ = parry_duration_; // 패링 성공 시 지속 시간만 적용
        }
        else {
            parry_timer_ = parry_cooldown_ + parry_duration_; // 패링 실패 시 쿨다운 적용
        }

        // 플레이어 이동 처리
        switch (direction_) {
        case 0: rect_.y -= parry_distance; break; // 위
        case 1: rect_.x += parry_distance; break; // 오른쪽
        case 2: rect_.y += parry_distance; break; // 아래
        case 3: rect_.x -= parry_distance; break; // 왼쪽
        }
    }
}


void Player::OnMonsterCollision(const SDL_Rect& monsterRect) {
    g_player_health -= 1;

}

void Player::SetParrying(bool parrying) {
    is_parrying_ = parrying;
}

bool Player::IsParrying() const {
    return is_parrying_;
}

SDL_Rect Player::GetRect() const {
    // 충돌 범위를 줄이기 위해 크기를 줄여서 반환
    SDL_Rect smaller_rect = rect_;
    smaller_rect.w *= 0.5;  // 너비를 50%로 줄임
    smaller_rect.h *= 0.6;  // 높이를 60%로 줄임
    return smaller_rect;
}

void Player::SetPosition(int x, int y) {
    rect_.x = x;
    rect_.y = y;
}
