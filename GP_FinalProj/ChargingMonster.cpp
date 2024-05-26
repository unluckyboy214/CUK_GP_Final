#include "ChargingMonster.h"
#include "globals.h"
#include <cmath>
#include <iostream>
#include <SDL_image.h> // SDL_image ��� ���� ����

constexpr float MONSTER_SPEED = 400.0f; // Adjust this value as needed
constexpr int DETECTION_RANGE = 300; // Detection range to start charging
constexpr float IDLE_DELAY = 0.5f; // Delay between idle checks in seconds
constexpr float CHARGE_DURATION = 1.0f; // Time to charge before running
constexpr float STUN_DURATION = 3.0f; // Time to stay stunned

ChargingMonster::ChargingMonster(int x, int y)
    : Monster(x, y), state(Idle), stateTimer(IDLE_DELAY), targetX(0), targetY(0), directionX(0), directionY(0), currentFrame(0), animationTime(0.0f), animationSpeed(0.1f) {
    LoadTextures();
}

void ChargingMonster::LoadTextures() {
    // Idle textures
    std::vector<std::string> idleFrameFiles = {
        "../../Resource/Monster/charge_frame1.png",
        "../../Resource/Monster/charge_frame2.png",
        "../../Resource/Monster/charge_frame3.png",
        "../../Resource/Monster/charge_frame4.png",
        "../../Resource/Monster/charge_frame5.png"
    };
    for (const auto& file : idleFrameFiles) {
        SDL_Surface* temp_surface = IMG_Load(file.c_str());
        if (temp_surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
            if (texture) {
                idleTextures.push_back(texture);
            }
            SDL_FreeSurface(temp_surface);
        }
    }

    // Charging textures
    std::vector<std::string> chargingFrameFiles = {
        "../../Resource/Monster/charge_frame1.png",
        "../../Resource/Monster/charge_frame2.png",
        "../../Resource/Monster/charge_frame3.png",
        "../../Resource/Monster/charge_frame4.png",
        "../../Resource/Monster/charge_frame5.png"
    };
    for (const auto& file : chargingFrameFiles) {
        SDL_Surface* temp_surface = IMG_Load(file.c_str());
        if (temp_surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
            if (texture) {
                chargingTextures.push_back(texture);
            }
            SDL_FreeSurface(temp_surface);
        }
    }

    // Running textures
    std::vector<std::string> runningFrameFiles = {
        "../../Resource/Monster/charge_run_frame1.png",
        "../../Resource/Monster/charge_run_frame2.png",
        "../../Resource/Monster/charge_run_frame3.png"
    };
    for (const auto& file : runningFrameFiles) {
        SDL_Surface* temp_surface = IMG_Load(file.c_str());
        if (temp_surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
            if (texture) {
                runningTextures.push_back(texture);
            }
            SDL_FreeSurface(temp_surface);
        }
    }

    // Stunned texture
    SDL_Surface* temp_surface = IMG_Load("../../Resource/Monster/charge_stun_frame.png");
    if (temp_surface) {
        stunnedTexture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
        SDL_FreeSurface(temp_surface);
    }
}

void ChargingMonster::Update(float deltaTime, const SDL_Rect& playerRect) {
    AdvanceFrame(deltaTime);
    stateTimer -= deltaTime;

    switch (state) {
    case Idle:
        if (stateTimer <= 0.0f) {
            stateTimer = IDLE_DELAY;
            if (std::abs(playerRect.x - x) <= DETECTION_RANGE && std::abs(playerRect.y - y) <= DETECTION_RANGE) {
                state = Charging;
                stateTimer = CHARGE_DURATION;
                directionX = playerRect.x - x;
                directionY = playerRect.y - y;
                float distance = std::sqrt(directionX * directionX + directionY * directionY);
                if (distance > 0) {
                    directionX /= distance;
                    directionY /= distance;
                }
            }
        }
        break;
    case Charging:
        if (stateTimer <= 0.0f) {
            state = Running;
        }
        break;
    case Running: {
        int nextX = x + static_cast<int>(directionX * MONSTER_SPEED * deltaTime);
        int nextY = y + static_cast<int>(directionY * MONSTER_SPEED * deltaTime);

        SDL_Rect monsterRect = { nextX, nextY, 128, 128 };
        bool collisionDetected = false;

        for (const auto& obstacle : g_obstacles) {
            if (SDL_HasIntersection(&monsterRect, &obstacle)) {
                collisionDetected = true;
                break;
            }
        }

        if (nextX <= 0 || nextX >= WINDOW_WIDTH - monsterRect.w || nextY <= 0 || nextY >= WINDOW_HEIGHT - monsterRect.h) {
            collisionDetected = true;
        }

        if (collisionDetected) {
            state = Stunned;
            stateTimer = STUN_DURATION;
        }
        else {
            x = nextX;
            y = nextY;
        }
        break;
    }
    case Stunned:
        if (stateTimer <= 0.0f) {
            state = Idle;
            stateTimer = IDLE_DELAY; // Reset idle delay
        }
        break;
    }
}

void ChargingMonster::AdvanceFrame(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= animationSpeed) {
        animationTime = 0.0f;
        currentFrame++;
        if (state == Idle) {
            currentFrame %= idleTextures.size();
        }
        else if (state == Charging) {
            currentFrame %= chargingTextures.size();
        }
        else if (state == Running) {
            currentFrame %= runningTextures.size();
        }
    }
}

void ChargingMonster::Render() {
    SDL_Rect dstRect = { x, y, 128, 128 }; // Example size, adjust as needed
    SDL_Texture* currentTexture = nullptr;

    switch (state) {
    case Idle:
        if (!idleTextures.empty()) {
            currentTexture = idleTextures[currentFrame % idleTextures.size()];
        }
        break;
    case Charging:
        if (!chargingTextures.empty()) {
            currentTexture = chargingTextures[currentFrame % chargingTextures.size()];
        }
        break;
    case Running:
        if (!runningTextures.empty()) {
            currentTexture = runningTextures[currentFrame % runningTextures.size()];
        }
        break;
    case Stunned:
        currentTexture = stunnedTexture;
        break;
    }

    if (currentTexture) {
        SDL_RenderCopy(g_renderer, currentTexture, NULL, &dstRect);
    }
}

void ChargingMonster::ResetStateTimer(float time) {
    stateTimer = time;
}
