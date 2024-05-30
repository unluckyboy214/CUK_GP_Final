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
#include "LastBoss.h" // LastBoss 추가
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
    LastBoss lastboss; // LastBoss 객체 생성
    Player player;
    Chisam chisam(WINDOW_WIDTH / 20, WINDOW_HEIGHT / 20, g_renderer, font);

    while (g_flag_running) {
        Uint32 cur_time_ms = SDL_GetTicks();
        float deltaTime = (cur_time_ms - g_last_time_ms) / 1000.0f;
        if (cur_time_ms - g_last_time_ms < (1000 / g_frame_per_sec))
            continue;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                g_flag_running = false;
            }
            chisam.HandleEvents(e);

            // 현재 맵의 몬스터 목록을 player.HandleEvents에 전달
            switch (g_current_game_phase) {
            case PHASE_Entrance:
                player.HandleEvents(e, entrance.GetMonsters());
                break;
            case PHASE_KimSuHwan:
                player.HandleEvents(e, kimsuhwan.GetMonsters());
                break;
            case PHASE_Hall:
                player.HandleEvents(e, hall.GetMonsters());
                break;
            /*case PHASE_Nicols1:
                player.HandleEvents(e, nicols1.GetMonsters());
                break;
            case PHASE_Nicols2:
                player.HandleEvents(e, nicols2.GetMonsters());
                break;
            case PHASE_Nicols3:
                player.HandleEvents(e, nicols3.GetMonsters());
                break;
            case PHASE_Maria:
                player.HandleEvents(e, maria.GetMonsters());
                break;
            case PHASE_Virtus:
                player.HandleEvents(e, virtus.GetMonsters());
                break;
            case PHASE_Bambino:
                player.HandleEvents(e, bambino.GetMonsters());
                break;
            case PHASE_Dasol:
                player.HandleEvents(e, dasol.GetMonsters());
                break;
            case PHASE_Sophiebara:
                player.HandleEvents(e, sophiebara.GetMonsters());
                break;
            case PHASE_Michael:
                player.HandleEvents(e, michael.GetMonsters());
                break;
            case PHASE_LastBoss:
                player.HandleEvents(e, lastboss.GetMonsters());
                break; */
            }
        }

        player.Update(deltaTime);

        if (g_player_health <= 0) {
            g_current_game_phase = PHASE_Entrance;
            g_player_health = 5;
        }

        bool showMinimapAndHealth = true;

        switch (g_current_game_phase) {
        case PHASE_Entrance:
            minimap.UpdatePlayerPosition(0);
            entrance.HandleEvents();
            entrance.Update(deltaTime);
            entrance.Render();
            chisam.Render();
            break;
        case PHASE_KimSuHwan:
            minimap.UpdatePlayerPosition(1);
            kimsuhwan.HandleEvents();
            kimsuhwan.Update(deltaTime);
            kimsuhwan.Render();
            break;
        case PHASE_Hall:
            minimap.UpdatePlayerPosition(2);
            hall.HandleEvents();
            hall.Update(deltaTime);
            hall.Render();
            break;
        case PHASE_Nicols1:
            minimap.UpdatePlayerPosition(3);
            nicols1.HandleEvents();
            nicols1.Update(deltaTime);
            nicols1.Render();
            break;
        case PHASE_Nicols2:
            minimap.UpdatePlayerPosition(4);
            nicols2.HandleEvents();
            nicols2.Update(deltaTime);
            nicols2.Render();
            break;
        case PHASE_Nicols3:
            minimap.UpdatePlayerPosition(5);
            nicols3.HandleEvents();
            nicols3.Update(deltaTime);
            nicols3.Render();
            break;
        case PHASE_Maria:
            minimap.UpdatePlayerPosition(6);
            maria.HandleEvents();
            maria.Update(deltaTime);
            maria.Render();
            break;
        case PHASE_Virtus:
            minimap.UpdatePlayerPosition(7);
            virtus.HandleEvents();
            virtus.Update(deltaTime);
            virtus.Render();
            break;
        case PHASE_Bambino:
            minimap.UpdatePlayerPosition(8);
            bambino.HandleEvents();
            bambino.Update(deltaTime);
            bambino.Render();
            break;
        case PHASE_Dasol:
            minimap.UpdatePlayerPosition(9);
            dasol.HandleEvents();
            dasol.Update(deltaTime);
            dasol.Render();
            break;
        case PHASE_Sophiebara:
            minimap.UpdatePlayerPosition(10);
            sophiebara.HandleEvents();
            sophiebara.Update(deltaTime);
            sophiebara.Render();
            break;
        case PHASE_Michael:
            minimap.UpdatePlayerPosition(11);
            michael.HandleEvents();
            michael.Update(deltaTime);
            michael.Render();
            break;
        case PHASE_LastBoss:
            minimap.UpdatePlayerPosition(12);
            lastboss.HandleEvents();
            lastboss.Update(deltaTime);
            lastboss.Render();
            showMinimapAndHealth = !lastboss.showBossIntro; // 인트로가 아닌 경우에만 표시
            break;
        }

        player.Render();

        if (showMinimapAndHealth) {
            minimap.Render(g_player_destination_rect.x, g_player_destination_rect.y);
            health.Render();
        }

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
