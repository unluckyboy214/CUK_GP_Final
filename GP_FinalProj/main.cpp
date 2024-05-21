// main.cpp
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
#include "globals.h"  // Include globals
#include "GamePhases.h"  // Include game phases

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    g_window = SDL_CreateWindow("Dungeon of Catholic (Beta)", 500, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    InitGame();

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

    while (g_flag_running)
    {
        Uint32 cur_time_ms = SDL_GetTicks();
        float deltaTime = (cur_time_ms - g_last_time_ms) / 1000.0f;  // deltaTime °è»ê
        if (cur_time_ms - g_last_time_ms < (1000 / g_frame_per_sec))
            continue;

        // Check if player's health is 0
        if (g_player_health <= 0) {
            g_current_game_phase = PHASE_Entrance; // Or any phase you define for game over
            g_player_health = 5; // Reset health for new game start
        }

        if (g_current_game_phase == PHASE_Entrance)
        {
            entrance.HandleEvents();
            entrance.Update(deltaTime);
            entrance.Render();
        }
        else if (g_current_game_phase == PHASE_KimSuHwan)
        {
            kimsuhwan.HandleEvents();
            kimsuhwan.Update(deltaTime);
            kimsuhwan.Render();
        }
        else if (g_current_game_phase == PHASE_Hall)
        {
            hall.HandleEvents();
            hall.Update(deltaTime);
            hall.Render();
        }
        else if (g_current_game_phase == PHASE_Nicols1)
        {
            nicols1.HandleEvents();
            nicols1.Update(deltaTime);
            nicols1.Render();
        }
        else if (g_current_game_phase == PHASE_Nicols2)
        {
            nicols2.HandleEvents();
            nicols2.Update(deltaTime);
            nicols2.Render();
        }
        else if (g_current_game_phase == PHASE_Nicols3)
        {
            nicols3.HandleEvents();
            nicols3.Update(deltaTime);
            nicols3.Render();
        }
        else if (g_current_game_phase == PHASE_Maria)
        {
            maria.HandleEvents();
            maria.Update(deltaTime);
            maria.Render();
        }
        else if (g_current_game_phase == PHASE_Virtus)
        {
            virtus.HandleEvents();
            virtus.Update(deltaTime);
            virtus.Render();
        }
        else if (g_current_game_phase == PHASE_Bambino)
        {
            bambino.HandleEvents();
            bambino.Update(deltaTime);
            bambino.Render();
        }
        else if (g_current_game_phase == PHASE_Dasol)
        {
            dasol.HandleEvents();
            dasol.Update(deltaTime);
            dasol.Render();
        }
        else if (g_current_game_phase == PHASE_Sophiebara)
        {
            sophiebara.HandleEvents();
            sophiebara.Update(deltaTime);
            sophiebara.Render();
        }
        else if (g_current_game_phase == PHASE_Michael)
        {
            michael.HandleEvents();
            michael.Update(deltaTime);
            michael.Render();
        }
        else if (g_current_game_phase == PHASE_LastBoss)
        {
            lastboss.HandleEvents();
            lastboss.Update(deltaTime);
            lastboss.Render();
        }

        g_last_time_ms = cur_time_ms;
    }

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    ClearGame();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
