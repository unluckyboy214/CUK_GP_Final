#include "Map.h"
#include "GameClass.h"
#include <SDL_image.h>
#include <random>

Map::Map(const char* backgroundPath, const SDL_Rect& portalRect)
    : portal_rect_(portalRect)
{
    LoadBackground(backgroundPath);
    LoadPortal();
    // SpawnMonsters()는 여기서 호출하지 않습니다.
}

Map::~Map() {
    SDL_DestroyTexture(texture_);
    SDL_DestroyTexture(portal_texture);
    for (auto monster : monsters) {
        delete monster;
    }
}

void Map::LoadBackground(const char* path) {
    SDL_Surface* temp_surface = IMG_Load(path);
    texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
    destination_rectangle_ = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

void Map::LoadPortal() {
    SDL_Surface* portal_surface = IMG_Load("../../Resource/Map/portal.png");
    SDL_Surface* resized_portal_surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_Rect resized_portal_rect = { 0, 0, 100, 100 };
    SDL_BlitScaled(portal_surface, NULL, resized_portal_surface, &resized_portal_rect);
    SDL_FreeSurface(portal_surface);
    portal_texture = SDL_CreateTextureFromSurface(g_renderer, resized_portal_surface);
    SDL_FreeSurface(resized_portal_surface);

    // 포탈 위치를 12시 방향으로 조정
    portal_rect_.x = (WINDOW_WIDTH - portal_rect_.w) / 2;
    portal_rect_.y = 50; // 화면 상단에서 50 픽셀 아래에 위치
}

void Map::Update(float deltaTime) {
    player_.Update(deltaTime);

    if (SDL_HasIntersection(&player_.GetRect(), &portal_rect_)) {
        // 포탈과 충돌 시 다음 맵으로 전환
        TransitionToNextMap();
    }

    for (auto it = monsters.begin(); it != monsters.end();) {
        (*it)->Update(deltaTime, player_.GetRect());
        if ((*it)->CheckCollisionWithPlayer(player_.GetRect())) {
            g_player_health--;
            delete* it;
            it = monsters.erase(it);
            if (g_player_health <= 0) {
                // 게임 오버 처리 로직
                ResetMonsters();
                break;
            }
        }
        else {
            ++it;
        }
    }
}

void Map::Render() {
    SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, 0);
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
    player_.Render();
    SDL_RenderCopy(g_renderer, portal_texture, NULL, &portal_rect_);
    for (auto monster : monsters) {
        monster->Render();
    }
    SDL_RenderPresent(g_renderer);
}

void Map::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_flag_running = false;
            break;
        default:
            player_.HandleEvents(event);
            break;
        }
    }
}

void Map::ResetMonsters() {
    for (auto monster : monsters) {
        delete monster;
    }
    monsters.clear();
    SpawnMonsters();
}