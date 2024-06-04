#include "Tutorial.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include "ChargingMonster.h"
#include "globals.h"
#include "GamePhases.h"
#include <SDL_image.h>
#include <random>

Tutorial::Tutorial()
    : Map("../../Resource/Map/Tutorial.png", 3), showPortal(false) {  // maxMonsters 설정
    spawnDelay = 1.0f;  // 초기 몬스터 생성 지연 시간 설정

    // 포탈 이미지 로드
    SDL_Surface* portalSurface = IMG_Load("../../Resource/Map/portal.png");
    portalTexture = SDL_CreateTextureFromSurface(g_renderer, portalSurface);
    SDL_FreeSurface(portalSurface);

    // 포탈 이미지 크기 설정
    portalRect = { 350, 500, 100, 100 };
}

void Tutorial::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    for (int i = 0; i < 1; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new MovingMonster(x, y));
    }
    for (int i = 0; i < 1; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new RangedMonster(x, y));
    }
    for (int i = 0; i < 1; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new ChargingMonster(x, y));
    }

}

void Tutorial::SpawnMonster() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    if (monsters.size() < maxMonsters) {
        int x = disX(gen);
        int y = disY(gen);
        deathCount++;
        if (deathCount % 3 == 1) {
            monsters.push_back(new MovingMonster(x, y));
        }
        else if (deathCount % 3 == 2) {
            monsters.push_back(new RangedMonster(x, y));
        }
        else if (deathCount % 3 == 0) {
            monsters.push_back(new ChargingMonster(x, y));
        }
    }
}

void Tutorial::Update(float deltaTime) {
    Map::Update(deltaTime);

    // 포탈과 플레이어 충돌 확인
    SDL_Rect playerRect = player_.GetRect();
    if (showPortal && SDL_HasIntersection(&playerRect, &portalRect)) {
        // Entrance 맵으로 이동
        g_kill_count = 0;
        g_player_health = 10;
        g_current_game_phase = PHASE_Entrance;
        player_.SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }
}

void Tutorial::Render() {
    Map::Render();

    // 포탈 렌더링
    if (showPortal) {
        SDL_RenderCopy(g_renderer, portalTexture, nullptr, &portalRect);
    }
}

void Tutorial::HandleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_c) {
            // C키를 누르면 포탈 표시
            showPortal = true;
        }
    }
}

void Tutorial::ResetPortalCloaking() {
    showPortal = false;
}