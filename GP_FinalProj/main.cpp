#include "GameClass.h"
#include "Entrance.h"
#include "KimSuHwan.h"
#include "Hall.h"
#include "Nicols1.h"
#include "Nicols2.h"
#include "Nicols3.h"
#include "Maria.h"
#include "Virtus.h"
#include "Bambino.h"
#include "Dasol.h"
#include "Sophiebara.h"
#include "Michael.h"
#include "LastBoss.h"
#include "globals.h"
#include "GamePhases.h"
#include "Minimap.h"
#include "Health.h"
#include "Chisam.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL_image.h> // Include SDL_image

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG); // Initialize SDL_image

    TTF_Font* font = TTF_OpenFont("../../Resource/YEONGJUSeonbi.ttf", 24); // 적절한 경로로 변경
    g_window = SDL_CreateWindow("Dungeon of Catholic (Beta)", 500, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    InitGame();

    Minimap minimap(g_renderer);
    Health health(g_renderer);

    Entrance entrance;
    KimSuHwan kimsuhwan;
    Hall hall;
    Nicols1 nicols1;
    Nicols2 nicols2;
    Nicols3 nicols3;
    Maria maria;
    Virtus virtus;
    Bambino bambino;
    Dasol dasol;
    Sophiebara sophiebara;
    Michael michael;
    LastBoss lastboss;
    Player player; // Player 객체 생성
    // Chisam 객체 생성
    Chisam chisam(WINDOW_WIDTH / 20, WINDOW_HEIGHT / 20, g_renderer, font);

    while (g_flag_running) {

        Uint32 cur_time_ms = SDL_GetTicks();
        float deltaTime = (cur_time_ms - g_last_time_ms) / 1000.0f;  // deltaTime 계산
        if (cur_time_ms - g_last_time_ms < (1000 / g_frame_per_sec))
            continue;


        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                g_flag_running = false;
            }
            chisam.HandleEvents(e); // Chisam 이벤트 처리
            player.HandleEvents(e); // Player 이벤트 처리
        }

        // 플레이어 업데이트
        player.Update(deltaTime);

        // Check if player's health is 0
        if (g_player_health <= 0) {
            g_current_game_phase = PHASE_Entrance; // Or any phase you define for game over
            g_player_health = 5; // Reset health for new game start
        }

        // 맵 전환 시 minimap 아이콘 업데이트
        if (g_current_game_phase == PHASE_Entrance) {
            minimap.UpdatePlayerPosition(0); // 첫 번째 맵
            entrance.HandleEvents();
            entrance.Update(deltaTime);
            entrance.Render();
            chisam.Render(); // Render Chisam
        }
        else if (g_current_game_phase == PHASE_KimSuHwan) {
            minimap.UpdatePlayerPosition(1); // 두 번째 맵
            kimsuhwan.HandleEvents();
            kimsuhwan.Update(deltaTime);
            kimsuhwan.Render();
        }
        else if (g_current_game_phase == PHASE_Hall) {
            minimap.UpdatePlayerPosition(2); // 세 번째 맵
            hall.HandleEvents();
            hall.Update(deltaTime);
            hall.Render();
        }
        else if (g_current_game_phase == PHASE_Nicols1) {
            minimap.UpdatePlayerPosition(3); // 네 번째 맵
            nicols1.HandleEvents();
            nicols1.Update(deltaTime);
            nicols1.Render();
        }
        else if (g_current_game_phase == PHASE_Nicols2) {
            minimap.UpdatePlayerPosition(4); // 다섯 번째 맵
            nicols2.HandleEvents();
            nicols2.Update(deltaTime);
            nicols2.Render();
        }
        else if (g_current_game_phase == PHASE_Nicols3) {
            minimap.UpdatePlayerPosition(5); // 여섯 번째 맵
            nicols3.HandleEvents();
            nicols3.Update(deltaTime);
            nicols3.Render();
        }
        else if (g_current_game_phase == PHASE_Maria) {
            minimap.UpdatePlayerPosition(6); // 일곱 번째 맵
            maria.HandleEvents();
            maria.Update(deltaTime);
            maria.Render();
        }
        else if (g_current_game_phase == PHASE_Virtus) {
            minimap.UpdatePlayerPosition(7); // 여덟 번째 맵
            virtus.HandleEvents();
            virtus.Update(deltaTime);
            virtus.Render();
        }
        else if (g_current_game_phase == PHASE_Bambino) {
            minimap.UpdatePlayerPosition(8); // 아홉 번째 맵
            bambino.HandleEvents();
            bambino.Update(deltaTime);
            bambino.Render();
        }
        else if (g_current_game_phase == PHASE_Dasol) {
            minimap.UpdatePlayerPosition(9); // 열 번째 맵
            dasol.HandleEvents();
            dasol.Update(deltaTime);
            dasol.Render();
        }
        else if (g_current_game_phase == PHASE_Sophiebara) {
            minimap.UpdatePlayerPosition(10); // 열한 번째 맵
            sophiebara.HandleEvents();
            sophiebara.Update(deltaTime);
            sophiebara.Render();
        }
        else if (g_current_game_phase == PHASE_Michael) {
            minimap.UpdatePlayerPosition(11); // 열두 번째 맵
            michael.HandleEvents();
            michael.Update(deltaTime);
            michael.Render();
        }
        else if (g_current_game_phase == PHASE_LastBoss) {
            minimap.UpdatePlayerPosition(12); // 열세 번째 맵
            lastboss.HandleEvents();
            lastboss.Update(deltaTime);
            lastboss.Render();
        }

        minimap.Render(g_player_destination_rect.x, g_player_destination_rect.y);
        health.Render();

        SDL_RenderPresent(g_renderer);
        g_last_time_ms = cur_time_ms;
    }

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    ClearGame();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
