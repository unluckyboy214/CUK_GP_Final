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
#include "Intro.h"
#include "GameOver.h"
#include "Pause.h"
#include "Tutorial.h"
#include "Ending.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL_image.h>

void SetPlayerToCenter(Player& player) {
    player.SetPosition(WINDOW_WIDTH / 2 - player.GetRect().w / 2, WINDOW_HEIGHT / 2 - player.GetRect().h / 2);
}

void RenderKillCount() {
    SDL_Color color = { 255, 0, 0, 255 };
    int requiredKillCount = 0;

    switch (g_current_game_phase) {
    case PHASE_Entrance:
        requiredKillCount = 3;
        break;
    case PHASE_KimSuHwan:
        requiredKillCount = 4;
        break;
    case PHASE_Hall:
        requiredKillCount = 5;
        break;
    case PHASE_Nicols1:
        requiredKillCount = 6;
        break;
    case PHASE_Dasol:
        requiredKillCount = 7;
        break;
    case PHASE_Sophiebara:
        requiredKillCount = 8;
        break;
    case PHASE_Michael:
        requiredKillCount = 9;
        break;
    default:
        requiredKillCount = 0;
        break;
    }

    std::string killCountText = "Kills: " + std::to_string(g_kill_count) + " / " + std::to_string(requiredKillCount);
    SDL_Surface* surface = TTF_RenderText_Solid(g_font, killCountText.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);

    int text_width = surface->w;
    int text_height = surface->h;
    int text_margin_top = 10;
    SDL_FreeSurface(surface);

    // Set background dimensions slightly larger than text dimensions
    int padding = 10; // Additional padding on the left and right
    SDL_Rect backgroundRect = { WINDOW_WIDTH / 2 - text_width / 2 - 50 - padding, text_margin_top - 5, text_width + padding * 2, text_height + 10 };

    // Render gray background
    SDL_SetRenderDrawColor(g_renderer, 192, 192, 192, 255); // Gray
    SDL_RenderFillRect(g_renderer, &backgroundRect);

    // Render darker gray border
    SDL_SetRenderDrawColor(g_renderer, 128, 128, 128, 255); // Darker Gray
    SDL_RenderDrawRect(g_renderer, &backgroundRect);

    // Reset color for text rendering
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255); // Black

    SDL_Rect renderQuad = { WINDOW_WIDTH / 2 - text_width / 2 - 50, text_margin_top, text_width, text_height };
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

void ResetGame(Entrance& entrance, KimSuHwan& kimsuhwan, Hall& hall, Nicols1& nicols1, Dasol& dasol, Sophiebara& sophiebara, Michael& michael, Player& player) {
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
    SetPlayerToCenter(player);
    ResetDirectionKeys(); // 방향 키 상태 초기화
    ClearEventQueue(); // 이벤트 큐 초기화
}

void ChangePhase(int newPhase) {
    static int lastPhase = -1;

    if (newPhase == PHASE_GameOver || newPhase == PHASE_Ending) {
        StopBackgroundMusic();
    }

    switch (newPhase) {
    case PHASE_Intro:
        PlayBackgroundMusic("../../Resource/Sound/Bgm/BG_Intro.mp3");
        break;
    case PHASE_Tutorial:
    case PHASE_Entrance:
        PlayBackgroundMusic("../../Resource/Sound/Bgm/BG1.mp3");
        break;
    case PHASE_KimSuHwan:
    case PHASE_Hall:
    case PHASE_Nicols1:
    case PHASE_Dasol:
    case PHASE_Sophiebara:
    case PHASE_Michael:
        if (lastPhase != PHASE_Entrance && lastPhase != PHASE_KimSuHwan && lastPhase != PHASE_Hall &&
            lastPhase != PHASE_Nicols1 && lastPhase != PHASE_Dasol && lastPhase != PHASE_Sophiebara && lastPhase != PHASE_Michael) {
            PlayBackgroundMusic("../../Resource/Sound/Bgm/BG1.mp3");
        }
        break;
    case PHASE_GameOver:
        PlayBackgroundMusic("../../Resource/Sound/Bgm/GameOver.mp3");
        break;
    case PHASE_Ending:
        PlayBackgroundMusic("../../Resource/Sound/Bgm/Ending.mp3");
        break;
    }

    g_current_game_phase = newPhase;
    lastPhase = newPhase;
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
    Gameover gameover;
    Pause pause;
    Tutorial tutorial;
    Entrance entrance;
    KimSuHwan kimsuhwan;
    Hall hall;
    Nicols1 nicols1;
    Dasol dasol;
    Sophiebara sophiebara;
    Michael michael;
    Ending ending;
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
                    ResetGame(entrance, kimsuhwan, hall, nicols1, dasol, sophiebara, michael, player);
                    g_reset_game = false;
                }
            }
            else if (g_current_game_phase == PHASE_GameOver) {
                gameover.HandleEvents(e);
                if (g_current_game_phase == PHASE_Intro) {
                    ResetGame(entrance, kimsuhwan, hall, nicols1, dasol, sophiebara, michael, player);
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
                if (g_current_game_phase != PHASE_Intro && g_current_game_phase != PHASE_GameOver) {
                    g_paused_game_phase = g_current_game_phase;
                    g_current_game_phase = PHASE_Pause;
                }
            }
            else {
                chisam.HandleEvents(e);

                switch (g_current_game_phase) {
                case PHASE_Tutorial:
                    tutorial.HandleEvent(e);
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
                case PHASE_Ending:
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
        else if (g_current_game_phase == PHASE_Ending) {
            ending.Update(deltaTime);
            ending.Render();
        }
        else {
            player.Update(deltaTime);

            if (g_player_health < 1) {
                ChangePhase(PHASE_GameOver);  // Changed to use ChangePhase function
            }

            if (g_kill_count >= 3 && g_current_game_phase == PHASE_Entrance) {
                ChangePhase(PHASE_KimSuHwan);
                g_kill_count = 0;
                kimsuhwan.ResetMonsters();
                SetPlayerToCenter(player);
            }
            else if (g_kill_count >= 4 && g_current_game_phase == PHASE_KimSuHwan) {
                ChangePhase(PHASE_Hall);
                g_kill_count = 0;
                hall.ResetMonsters();
                SetPlayerToCenter(player);
            }
            else if (g_kill_count >= 5 && g_current_game_phase == PHASE_Hall) {
                ChangePhase(PHASE_Nicols1);
                g_kill_count = 0;
                nicols1.ResetMonsters();
                SetPlayerToCenter(player);
            }
            else if (g_kill_count >= 6 && g_current_game_phase == PHASE_Nicols1) {
                ChangePhase(PHASE_Dasol);
                g_kill_count = 0;
                dasol.ResetMonsters();
                SetPlayerToCenter(player);
            }
            else if (g_kill_count >= 7 && g_current_game_phase == PHASE_Dasol) {
                ChangePhase(PHASE_Sophiebara);
                g_kill_count = 0;
                sophiebara.ResetMonsters();
                SetPlayerToCenter(player);
            }
            else if (g_kill_count >= 8 && g_current_game_phase == PHASE_Sophiebara) {
                ChangePhase(PHASE_Michael);
                g_kill_count = 0;
                michael.ResetMonsters();
                SetPlayerToCenter(player);
            }
            else if (g_kill_count >= 9 && g_current_game_phase == PHASE_Michael) {
                ChangePhase(PHASE_Ending);
                g_kill_count = 0;
                SetPlayerToCenter(player);
            }

            switch (g_current_game_phase) {
            case PHASE_Tutorial:
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
