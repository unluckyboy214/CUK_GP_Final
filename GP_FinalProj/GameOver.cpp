#include "Gameover.h"
#include "globals.h"
#include "GamePhases.h"
#include <SDL_image.h>

Gameover::Gameover() {
    // 배경 이미지 로드
    SDL_Surface* backgroundSurface = IMG_Load("../../Resource/Map/GameOver.png");
    backgroundTexture = SDL_CreateTextureFromSurface(g_renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // 배경 이미지 크기 설정
    backgroundRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

Gameover::~Gameover() {
    SDL_DestroyTexture(backgroundTexture);
}

void Gameover::Update(float deltaTime) {
    // Gameover 화면에서는 특별한 업데이트 로직이 없습니다.
}

void Gameover::Render() {
    SDL_RenderCopy(g_renderer, backgroundTexture, nullptr, &backgroundRect);
}

void Gameover::HandleEvents(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        // 마우스 버튼이 눌리면 PHASE_Intro로 전환
        g_current_game_phase = PHASE_Intro;
    }
}