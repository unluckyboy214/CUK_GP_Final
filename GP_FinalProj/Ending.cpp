#include "Ending.h"
#include "globals.h"
#include <SDL_image.h>

Ending::Ending() {
    // 배경 이미지 로드
    SDL_Surface* backgroundSurface = IMG_Load("../../Resource/Map/Ending.png");
    backgroundTexture = SDL_CreateTextureFromSurface(g_renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // 배경 이미지 크기 설정
    backgroundRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

Ending::~Ending() {
    SDL_DestroyTexture(backgroundTexture);
}

void Ending::Update(float deltaTime) {
    // Ending 화면에서는 특별한 업데이트 로직이 없습니다.
}

void Ending::Render() {
    SDL_RenderCopy(g_renderer, backgroundTexture, nullptr, &backgroundRect);
}
