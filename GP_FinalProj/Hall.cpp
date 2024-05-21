#include "GameClass.h"
#include "Hall.h"
#include "ChargingMonster.h"
#include <algorithm>
#include <random>

Hall::Hall() {
    // 배경 로드
    SDL_Surface* temp_surface = IMG_Load("../../Resource/Map/Hall.png");
    texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
    destination_rectangle_ = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    // 캐릭터 로드
    SDL_Surface* flight_sheet_surface = IMG_Load("../../Resource/Character/Isacc.png");
    g_flight_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, flight_sheet_surface);
    SDL_FreeSurface(flight_sheet_surface);

    // 포탈 로드
    SDL_Surface* portal_surface = IMG_Load("../../Resource/Map/portal.png");
    SDL_Surface* resized_portal_surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_Rect resized_portal_rect = { 0, 0, 100, 100 };
    SDL_BlitScaled(portal_surface, NULL, resized_portal_surface, &resized_portal_rect);
    SDL_FreeSurface(portal_surface);

    portal_texture = SDL_CreateTextureFromSurface(g_renderer, resized_portal_surface);
    SDL_FreeSurface(resized_portal_surface);

    // 포탈 위치 조정
    portal_rect_HtoK = { (WINDOW_WIDTH - 100) / 2, 500, 100, 100 };
    portal_rect_HtoN1 = { 700, (WINDOW_HEIGHT - 100) / 2, 100, 100 };

    // 몬스터 생성
    SpawnMonsters();
}

Hall::~Hall() {
    SDL_DestroyTexture(texture_);
    SDL_DestroyTexture(g_flight_sheet_texture);
    SDL_DestroyTexture(portal_texture);
    for (auto monster : monsters) {
        delete monster;
    }
}

void Hall::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128); // Adjusting for monster size
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128); // Adjusting for monster size

    for (int i = 0; i < 3; ++i) { // Create 3 charging monsters
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new ChargingMonster(x, y));
    }
}

void Hall::ResetMonsters() {
    for (auto monster : monsters) {
        delete monster;
    }
    monsters.clear();
    SpawnMonsters();
}

void Hall::Update(float deltaTime) {
    const float moveSpeed = 500.0f;

    // 입력 상태에 따라 이동
    if (g_move_left) {
        g_player_destination_rect.x -= moveSpeed * deltaTime;
        g_player_direction = PlayerDirection::LEFT;
    }
    if (g_move_right) {
        g_player_destination_rect.x += moveSpeed * deltaTime;
        g_player_direction = PlayerDirection::RIGHT;
    }
    if (g_move_up) {
        g_player_destination_rect.y -= moveSpeed * deltaTime;
        g_player_direction = PlayerDirection::UP;
    }
    if (g_move_down) {
        g_player_destination_rect.y += moveSpeed * deltaTime;
        g_player_direction = PlayerDirection::DOWN;
    }

    // 윈도우 경계를 벗어나지 않도록 제한
    g_player_destination_rect.x = std::max(0, std::min(WINDOW_WIDTH - g_player_destination_rect.w - 40, g_player_destination_rect.x));
    g_player_destination_rect.y = std::max(0, std::min(WINDOW_HEIGHT - g_player_destination_rect.h - 40, g_player_destination_rect.y));

    // 포탈과 캐릭터 충돌 확인
    if (SDL_HasIntersection(&g_player_destination_rect, &portal_rect_HtoK)) {
        g_current_game_phase = PHASE_KimSuHwan;
        g_player_destination_rect = { WINDOW_WIDTH / 2, 110, 100, 100 };
        g_player_direction = PlayerDirection::DOWN;
    }
    if (SDL_HasIntersection(&g_player_destination_rect, &portal_rect_HtoN1)) {
        g_current_game_phase = PHASE_Nicols1;
        g_player_destination_rect = { 110, WINDOW_HEIGHT / 2, 100, 100 };
        g_player_direction = PlayerDirection::RIGHT;
    }

    // 몬스터와 플레이어 충돌 확인
    for (auto it = monsters.begin(); it != monsters.end();) {
        (*it)->Update(deltaTime, g_player_destination_rect); // Update each monster's animation and movement

        if ((*it)->CheckCollisionWithPlayer(g_player_destination_rect)) {
            g_player_health--;
            delete* it;
            it = monsters.erase(it);

            if (g_player_health <= 0) {
                // 게임 오버 처리
                g_current_game_phase = PHASE_Entrance;
                g_player_destination_rect = { WINDOW_WIDTH / 2, 110, 100, 100 };
                g_player_direction = PlayerDirection::DOWN;
                g_player_health = 5;
                ResetMonsters(); // Reset monsters when health is depleted and player respawns
                break;
            }
        }
        else {
            ++it;
        }
    }
}

void Hall::Render() {
    SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, 0);
    SDL_RenderClear(g_renderer);

    // 배경
    SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

    // 캐릭터
    SDL_Rect flightRect = g_player_destination_rect;
    SDL_RenderCopy(g_renderer, g_flight_sheet_texture, NULL, &flightRect);

    // 포탈 그리기
    SDL_RenderCopy(g_renderer, portal_texture, NULL, &portal_rect_HtoK);
    SDL_RenderCopy(g_renderer, portal_texture, NULL, &portal_rect_HtoN1);

    // 플레이어 체력 그리기
    for (int i = 0; i < g_player_health; i++) {
        SDL_Rect healthRect = { 10 + i * 20, 10, 20, 20 };
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(g_renderer, &healthRect);
    }

    // 몬스터 그리기
    for (auto monster : monsters) {
        monster->Render();
    }

    SDL_RenderPresent(g_renderer);
}

void Hall::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_flag_running = false;
            break;

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

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_RIGHT) {
                g_current_game_phase = PHASE_Nicols1;
            }
            break;
        }
    }
}
