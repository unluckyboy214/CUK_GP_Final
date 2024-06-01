// Phase.cpp
#include "Phase.h"
#include "GameClass.h"
#include <SDL_image.h>

Phase::Phase(const char* backgroundPath) {
    LoadBackground(backgroundPath);
    player_.SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

Phase::~Phase() {
    SDL_DestroyTexture(background_texture_);
    ResetMonsters();
}

void Phase::LoadBackground(const char* path) {
    SDL_Surface* temp_surface = IMG_Load(path);
    background_texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    background_rect_ = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

void Phase::AddPortal(int x, int y, int dx, int dy) {
    portals_.emplace_back(x, y, dx, dy);
}

void Phase::Update(float deltaTime) {
    player_.Update(deltaTime);

    for (const auto& portal : portals_) {
        if (portal.IsColliding(player_.GetRect())) {
            g_current_phase_x += portal.GetDX();
            g_current_phase_y += portal.GetDY();
            player_.SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            break;
        }
    }

    for (auto it = monsters_.begin(); it != monsters_.end();) {
        (*it)->Update(deltaTime, player_.GetRect());

        if ((*it)->CheckCollisionWithPlayer(player_.GetRect())) {
            g_player_health--;
            delete* it;
            it = monsters_.erase(it);

            if (g_player_health <= 0) {
                // 게임 오버 처리
                g_current_phase_x = 0;
                g_current_phase_y = 0;
                g_player_health = 5;
                player_.SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                ResetMonsters();
                break;
            }
        }
        else {
            ++it;
        }
    }
}

void Phase::Render() {
    SDL_RenderCopy(g_renderer, background_texture_, NULL, &background_rect_);
    player_.Render();

    for (const auto& portal : portals_) {
        portal.Render();
    }

    for (const auto& monster : monsters_) {
        monster->Render();
    }
}

void Phase::HandleEvents() {
    player_.HandleEvents();
}

void Phase::ResetMonsters() {
    for (auto monster : monsters_) {
        delete monster;
    }
    monsters_.clear();
    SpawnMonsters();
}