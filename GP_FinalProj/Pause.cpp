// Pause.cpp
#include "Pause.h"
#include "globals.h"
#include "GamePhases.h"
#include <SDL_image.h>

Pause::Pause() {
    LoadTextures();

    backgroundRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    continueRect = { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 150, 200, 50 };
    retryRect = { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, 200, 50 };
    quitRect = { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 50, 200, 50 };
}

Pause::~Pause() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(continueTexture);
    SDL_DestroyTexture(retryTexture);
    SDL_DestroyTexture(quitTexture);
}

void Pause::LoadTextures() {
    backgroundTexture = IMG_LoadTexture(g_renderer, "../../Resource/Map/Pause_bg.png");
    continueTexture = IMG_LoadTexture(g_renderer, "../../Resource/Map/Pause_continue.png");
    retryTexture = IMG_LoadTexture(g_renderer, "../../Resource/Map/Pause_retry.png");
    quitTexture = IMG_LoadTexture(g_renderer, "../../Resource/Map/Pause_gamequit.png");
}

void Pause::Update(float deltaTime) {
    // 일시정지 화면에서는 업데이트 로직이 필요하지 않습니다.
}

void Pause::Render() {
    SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(backgroundTexture, 128);
    SDL_RenderCopy(g_renderer, backgroundTexture, NULL, &backgroundRect);
        
    SDL_RenderCopy(g_renderer, continueTexture, NULL, &continueRect);
    SDL_RenderCopy(g_renderer, retryTexture, NULL, &retryRect);
    SDL_RenderCopy(g_renderer, quitTexture, NULL, &quitRect);
}

void Pause::HandleEvents(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;

            if (x >= continueRect.x && x <= continueRect.x + continueRect.w &&
                y >= continueRect.y && y <= continueRect.y + continueRect.h) {
                // 계속하기 버튼 클릭 시 이전 페이즈로 돌아갑니다.
                g_current_game_phase = g_paused_game_phase;
            }
            else if (x >= retryRect.x && x <= retryRect.x + retryRect.w &&
                y >= retryRect.y && y <= retryRect.y + retryRect.h) {
                // 재시작 버튼 클릭 시 Intro 페이즈로 돌아가고 게임을 초기화합니다.
                g_current_game_phase = PHASE_Intro;
                g_reset_game = true; // 게임 초기화 플래그 설정
            }
            else if (x >= quitRect.x && x <= quitRect.x + quitRect.w &&
                y >= quitRect.y && y <= quitRect.y + quitRect.h) {
                // 종료 버튼 클릭 시 게임을 종료합니다.
                g_flag_running = false;
            }
        }
    }
    else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            // ESC 키를 누르면 이전 페이즈로 돌아갑니다.
            g_current_game_phase = g_paused_game_phase;
        }
    }
}