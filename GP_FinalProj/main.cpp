﻿#include "GameClass.h"
#include "Intro.h"
#include "Entrance.h"
#include "KimSuHwan.h"
#include "Hall.h"
#include "globals.h"
#include "GamePhases.h"
#include "Health.h"
#include "Chisam.h"
#include "Nicols1.h"
#include "Dasol.h"
#include "Sophiebara.h"
#include "Michael.h"
#include "LastBoss.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL_image.h>

void SetPlayerToCenter(Player& player) {
    player.SetPosition(WINDOW_WIDTH / 2 - player.GetRect().w / 2, WINDOW_HEIGHT / 2 - player.GetRect().h / 2);
}

void RenderKillCount() {
    SDL_Color color = { 255, 0, 0, 255 };
    std::string killCountText = "Kills: " + std::to_string(g_kill_count);
    SDL_Surface* surface = TTF_RenderText_Solid(g_font, killCountText.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);

    int text_width = surface->w;
    int text_height = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect renderQuad = { WINDOW_WIDTH / 2 - text_width / 2, 0, text_width, text_height };
    SDL_RenderCopy(g_renderer, texture, NULL, &renderQuad);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    TTF_Font* font = TTF_OpenFont("../../Resource/YEONGJUSeonbi.ttf", 24);
    g_font = font;
    g_window = SDL_CreateWindow("Dungeon of Catholic (Beta)", 500, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    InitGame();

    Health health(g_renderer);

    Intro intro;
    Entrance entrance;
    KimSuHwan kimsuhwan;
    Hall hall;
    Nicols1 nicols1;
    Dasol dasol;
    Sophiebara sophiebara;
    Michael michael;
    LastBoss lastboss;
    Player player;
    Chisam chisam(WINDOW_WIDTH / 20, WINDOW_HEIGHT / 20, g_renderer, font);

    SetPlayerToCenter(player);

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

            switch (g_current_game_phase) {
            case PHASE_Intro:
                intro.HandleEvents(e);
                break;
            case PHASE_Entrance:
                player.HandleEvents(e, entrance.GetMonsters());
                break;
            case PHASE_KimSuHwan:
                player.HandleEvents(e, kimsuhwan.GetMonsters());
                break;
            case PHASE_Hall:
                player.HandleEvents(e, hall.GetMonsters());
                break;
            case PHASE_Nicols1:
                player.HandleEvents(e, nicols1.GetMonsters());
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
                break;
            }
        }

        player.Update(deltaTime);

        if (g_player_health <= 0) {
            g_current_game_phase = PHASE_Entrance;
            g_player_health = 5;
            entrance.ResetMonsters();
            SetPlayerToCenter(player);
        }

        if (g_kill_count >= 10) {
            g_kill_count = 0;
            switch (g_current_game_phase) {
            case PHASE_Entrance:
                g_current_game_phase = PHASE_KimSuHwan;
                kimsuhwan.ResetMonsters();
                break;
            case PHASE_KimSuHwan:
                g_current_game_phase = PHASE_Hall;
                hall.ResetMonsters();
                break;
            case PHASE_Hall:
                g_current_game_phase = PHASE_Nicols1;
                nicols1.ResetMonsters();
                break;
            case PHASE_Nicols1:
                g_current_game_phase = PHASE_Dasol;
                dasol.ResetMonsters();
                break;
            case PHASE_Dasol:
                g_current_game_phase = PHASE_Sophiebara;
                sophiebara.ResetMonsters();
                break;
            case PHASE_Sophiebara:
                g_current_game_phase = PHASE_Michael;
                michael.ResetMonsters();
                break;
            case PHASE_Michael:
                g_current_game_phase = PHASE_LastBoss;
                lastboss.ResetMonsters();
                break;
            case PHASE_LastBoss:
                g_current_game_phase = PHASE_Entrance;
                entrance.ResetMonsters();
                break;
            }
            SetPlayerToCenter(player);
        }

        switch (g_current_game_phase) {
        case PHASE_Intro:
            intro.Update(deltaTime);
            intro.Render();
            break;
        case PHASE_Entrance:
            entrance.Update(deltaTime);
            entrance.Render();
            chisam.Render();
            break;
        case PHASE_KimSuHwan:
            kimsuhwan.Update(deltaTime);
            kimsuhwan.Render();
            break;
        case PHASE_Hall:
            hall.Update(deltaTime);
            hall.Render();
            break;
        case PHASE_Nicols1:
            nicols1.Update(deltaTime);
            nicols1.Render();
            break;
        case PHASE_Dasol:
            dasol.Update(deltaTime);
            dasol.Render();
            break;
        case PHASE_Sophiebara:
            sophiebara.Update(deltaTime);
            sophiebara.Render();
            break;
        case PHASE_Michael:
            michael.Update(deltaTime);
            michael.Render();
            break;
        case PHASE_LastBoss:
            lastboss.Update(deltaTime);
            lastboss.Render();
            break;
        }

        player.Render();
        RenderKillCount();
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
