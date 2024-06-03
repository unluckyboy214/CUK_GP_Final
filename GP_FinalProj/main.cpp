#include "GameClass.h"
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
#include "Intro.h"
#include "GameOver.h" // 추가
#include "Pause.h"
#include "Tutorial.h"
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

void ResetDirectionKeys() {
    g_move_left = false;
    g_move_right = false;
    g_move_up = false;
    g_move_down = false;
}

void ClearEventQueue() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // 모든 이벤트를 버립니다.
    }
}

void ResetGame(Entrance& entrance, KimSuHwan& kimsuhwan, Hall& hall, Nicols1& nicols1, Dasol& dasol, Sophiebara& sophiebara, Michael& michael, LastBoss& lastboss, Player& player) {
    g_current_game_phase = PHASE_Intro;
    g_player_health = 10;
    g_kill_count = 0;
    entrance.ResetMonsters();
    kimsuhwan.ResetMonsters();
    hall.ResetMonsters();
    nicols1.ResetMonsters();
    dasol.ResetMonsters();
    sophiebara.ResetMonsters();
    michael.ResetMonsters();
    lastboss.ResetMonsters();
    SetPlayerToCenter(player);
    ResetDirectionKeys(); // 방향 키 상태 초기화
    ClearEventQueue(); // 이벤트 큐 초기화
}

void ChangePhase(int newPhase) {
    g_current_game_phase = newPhase;
    switch (newPhase) {
    case PHASE_Intro:
        PlayBackgroundMusic("../../Resource/Sound/Bgm/BG_Intro.mp3");
        break;
    case PHASE_Entrance:
    case PHASE_KimSuHwan:
    case PHASE_Hall:
    case PHASE_Nicols1:
    case PHASE_Dasol:
    case PHASE_Sophiebara:
    case PHASE_Michael:
        PlayBackgroundMusic("../../Resource/Sound/Bgm/BG1.mp3");
        break;
    case PHASE_LastBoss:
        PlayBackgroundMusic("../../Resource/Sound/Bgm/LastBoss.mp3");
        break;
    case PHASE_GameOver:
        PlayBackgroundMusic("../../Resource/Sound/Bgm/GameOver.mp3");
        break;
    }
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
    Gameover gameover; // 추가
    Pause pause;
    Tutorial tutorial;
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

    PlayBackgroundMusic("../../Resource/Sound/Bgm/BG_Intro.mp3");

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

            if (g_current_game_phase == PHASE_Intro) {
                intro.HandleEvents(e);
                if (g_reset_game) {
                    ResetGame(entrance, kimsuhwan, hall, nicols1, dasol, sophiebara, michael, lastboss, player);
                    g_reset_game = false;
                }
            }
            else if (g_current_game_phase == PHASE_GameOver) {
                gameover.HandleEvents(e);
                if (g_current_game_phase == PHASE_Intro) {
                    ResetGame(entrance, kimsuhwan, hall, nicols1, dasol, sophiebara, michael, lastboss, player);
                    ChangePhase(PHASE_Intro);
                }
            }
            else if (g_current_game_phase == PHASE_Pause) {
                pause.HandleEvents(e);
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                    g_is_fading = true;
                }
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                if (g_current_game_phase != PHASE_Intro && g_current_game_phase != PHASE_Gameover) {
                    g_paused_game_phase = g_current_game_phase;
                    g_current_game_phase = PHASE_Pause;
                }
            }
            else {
                chisam.HandleEvents(e);

                switch (g_current_game_phase) {
                case PHASE_Tutorial:
                    player.HandleEvents(e, tutorial.GetMonsters());
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
        }

        if (g_current_game_phase == PHASE_Intro) {
            intro.Update(deltaTime);
            intro.Render();
        }
        else if (g_current_game_phase == PHASE_GameOver) {
            gameover.Update(deltaTime);
            gameover.Render();
        }
        else {
            player.Update(deltaTime);

            if (g_player_health < 1) {
                g_current_game_phase = PHASE_GameOver;
            }

            if (g_kill_count >= 10 && g_current_game_phase != PHASE_LastBoss) {
                g_kill_count = 0;
                switch (g_current_game_phase) {
                case PHASE_Tutorial: // Tutorial 페이즈 추가
                    ChangePhase(PHASE_Entrance);
                    entrance.ResetMonsters();
                    break;
                case PHASE_Entrance:
                    ChangePhase(PHASE_KimSuHwan);
                    kimsuhwan.ResetMonsters();
                    break;
                case PHASE_KimSuHwan:
                    ChangePhase(PHASE_Hall);
                    hall.ResetMonsters();
                    break;
                case PHASE_Hall:
                    ChangePhase(PHASE_Nicols1);
                    nicols1.ResetMonsters();
                    break;
                case PHASE_Nicols1:
                    ChangePhase(PHASE_Dasol);
                    dasol.ResetMonsters();
                    break;
                case PHASE_Dasol:
                    ChangePhase(PHASE_Sophiebara);
                    sophiebara.ResetMonsters();
                    break;
                case PHASE_Sophiebara:
                    ChangePhase(PHASE_Michael);
                    michael.ResetMonsters();
                    break;
                case PHASE_Michael:
                    ChangePhase(PHASE_LastBoss);
                    lastboss.ResetMonsters();
                    break;
                case PHASE_Pause:
                    pause.HandleEvents(e);
                    break;
                }
                SetPlayerToCenter(player);
            }
            else if (g_kill_count >= 7 && g_current_game_phase == PHASE_KimSuHwan) {
                ChangePhase(PHASE_Hall);
                g_kill_count = 0;
                hall.ResetMonsters();
                SetPlayerToCenter(player);
            }
            else if (g_kill_count >= 5 && g_current_game_phase == PHASE_Entrance) {
                ChangePhase(PHASE_KimSuHwan);
                g_kill_count = 0;
                kimsuhwan.ResetMonsters();
                SetPlayerToCenter(player);
            }

            switch (g_current_game_phase) {
            case PHASE_Tutorial: // Tutorial 페이즈 추가
                tutorial.Update(deltaTime);
                tutorial.Render();
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
            case PHASE_Pause:
                pause.Update(deltaTime);
                pause.Render();
                break;
            }

            player.Render();
            RenderKillCount();
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
