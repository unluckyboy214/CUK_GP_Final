// KimSuHwan.cpp
#include "GameClass.h"
#include "KimSuHwan.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include <algorithm>
#include <random>

KimSuHwan::KimSuHwan()
{
    // 텍스처 로드
    SDL_Surface* temp_surface = IMG_Load("../../Resource/Map/KimSuHwan.png");
    texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
    destination_rectangle_ = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    // 포탈 로드
    SDL_Surface* portal_surface = IMG_Load("../../Resource/Map/portal.png");
    SDL_Surface* resized_portal_surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_Rect resized_portal_rect = { 0, 0, 100, 100 };
    SDL_BlitScaled(portal_surface, NULL, resized_portal_surface, &resized_portal_rect);
    SDL_FreeSurface(portal_surface);

    portal_texture = SDL_CreateTextureFromSurface(g_renderer, resized_portal_surface);
    SDL_FreeSurface(resized_portal_surface);

    portal_rect_KtoE = { (WINDOW_WIDTH - 100) / 2, 500, 100, 100 };
    portal_rect_KtoH = { (WINDOW_WIDTH - 100) / 2, 0, 100, 100 };

    // 몬스터 생성
    SpawnMonsters();
}

KimSuHwan::~KimSuHwan()
{
    SDL_DestroyTexture(texture_);
    SDL_DestroyTexture(portal_texture);
    for (auto monster : monsters) {
        delete monster;
    }
}

void KimSuHwan::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128); // Adjusting for monster size
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128); // Adjusting for monster size

    for (int i = 0; i < 4; ++i) { // Create 4 moving monsters
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new MovingMonster(x, y));
    }
    for (int i = 0; i < 3; ++i) { // Create 3 ranged monsters
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new RangedMonster(x, y));
    }
}

void KimSuHwan::ResetMonsters() {
    for (auto monster : monsters) {
        delete monster;
    }
    monsters.clear();
    SpawnMonsters();
}

void KimSuHwan::Update(float deltaTime)
{
    player_.Update(deltaTime); // 플레이어 업데이트

    // 포탈과 캐릭터 충돌 확인
    if (SDL_HasIntersection(&player_.GetRect(), &portal_rect_KtoE))
    {
        g_current_game_phase = PHASE_Entrance;
        player_ = Player(); // 플레이어 초기화
        ResetMonsters(); // Reset monsters when leaving KimSuHwan map
    }
    if (SDL_HasIntersection(&player_.GetRect(), &portal_rect_KtoH))
    {
        g_current_game_phase = PHASE_Hall;
        player_ = Player(); // 플레이어 초기화
    }

    // 몬스터와 플레이어 충돌 확인 및 패링 처리
    for (auto it = monsters.begin(); it != monsters.end();) {
        (*it)->Update(deltaTime, player_.GetRect()); // Update each monster's animation and movement

        if ((*it)->CheckCollisionWithPlayer(player_.GetRect())) {
            if (player_.IsParrying()) { // 패링 상태이면
                dynamic_cast<MovingMonster*>(*it)->ParryEffect(player_.GetRect()); // 패링 효과 적용
                // 여기서 이펙트를 출력할 수 있습니다 (예: 패링 이펙트 출력 함수 호출)
            }
            else {
                g_player_health--;
                delete* it;
                it = monsters.erase(it);

                if (g_player_health <= 0) {
                    // 게임 오버 처리
                    g_current_game_phase = PHASE_Entrance;
                    player_ = Player(); // 플레이어 초기화
                    g_player_health = 5;
                    ResetMonsters(); // Reset monsters when health is depleted and player respawns
                    break;
                }
            }
        }
        else {
            ++it;
        }
    }
}

void KimSuHwan::Render()
{
    SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, 0);
    SDL_RenderClear(g_renderer);

    // 배경 그리기
    SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

    // 플레이어 그리기
    player_.Render();

    // 플레이어 체력 그리기
    for (int i = 0; i < g_player_health; i++)
    {
        SDL_Rect healthRect = { 10 + i * 20, 10, 20, 20 };
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(g_renderer, &healthRect);
    }

    // 포탈 그리기
    SDL_RenderCopy(g_renderer, portal_texture, NULL, &portal_rect_KtoE);
    SDL_RenderCopy(g_renderer, portal_texture, NULL, &portal_rect_KtoH);

    // 몬스터 그리기
    for (auto monster : monsters) {
        monster->Render();
    }

    SDL_RenderPresent(g_renderer);
}

void KimSuHwan::HandleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_flag_running = false;
            break;

        default:
            player_.HandleEvents(event); // 플레이어 이벤트 처리
            break;
        }
    }
}
