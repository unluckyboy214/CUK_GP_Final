#include "Intro.h"
#include "globals.h"
#include "GamePhases.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

Intro::Intro() {
    // 배경 이미지 로드
    SDL_Surface* backgroundSurface = IMG_Load("../../Resource/Map/Intro.png");
    backgroundTexture = SDL_CreateTextureFromSurface(g_renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // 배경 이미지 크기 설정
    backgroundRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    startButtonRect = { 520, 320, 200, 50 };
    exitButtonRect = { 520, 415, 200, 50 };

    // 효과음 로드 (미리 로드해서 메모리에서 재생)
    successSound = Mix_LoadWAV("../../Resource/Sound/Effect/1.mp3");
    if (!successSound) {
        std::cerr << "Error loading success sound: " << Mix_GetError() << std::endl;
    }
}

Intro::~Intro() {
    SDL_DestroyTexture(backgroundTexture);
    if (successSound) {
        Mix_FreeChunk(successSound);
    }
}

void Intro::Update(float deltaTime) {
    // Intro 화면에서는 특별한 업데이트 로직이 없습니다.
}

void Intro::Render() {
    SDL_RenderCopy(g_renderer, backgroundTexture, nullptr, &backgroundRect);
    // 버튼 렌더링 추가
}

void Intro::HandleEvents(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;

            if (x >= startButtonRect.x && x <= startButtonRect.x + startButtonRect.w &&
                y >= startButtonRect.y && y <= startButtonRect.y + startButtonRect.h) {
                g_current_game_phase = PHASE_Entrance;

                // 성공 사운드 재생
                if (successSound) {
                    Mix_VolumeChunk(successSound, MIX_MAX_VOLUME); // 볼륨 설정
                    Mix_PlayChannel(-1, successSound, 0);
                }
                else {
                    std::cerr << "Error: success sound is not loaded properly." << std::endl;
                }
            }
            else if (x >= exitButtonRect.x && x <= exitButtonRect.x + exitButtonRect.w &&
                y >= exitButtonRect.y && y <= exitButtonRect.y + exitButtonRect.h) {
                g_flag_running = false;
            }
        }
    }
}
