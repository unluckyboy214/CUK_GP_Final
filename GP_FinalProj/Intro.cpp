#include "Intro.h"
#include "globals.h"
#include "GamePhases.h"
#include <SDL_image.h>

Intro::Intro() {
    // ��� �̹��� �ε�
    SDL_Surface* backgroundSurface = IMG_Load("../../Resource/Map/Intro.png");
    backgroundTexture = SDL_CreateTextureFromSurface(g_renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // ��� �̹��� ũ�� ����
    backgroundRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    startButtonRect = { 520, 320, 200, 50 };
    exitButtonRect = { 520, 415, 200, 50 };
}

Intro::~Intro() {
    SDL_DestroyTexture(backgroundTexture);
}

void Intro::Update(float deltaTime) {
    // Intro ȭ�鿡���� Ư���� ������Ʈ ������ �����ϴ�.
}

void Intro::Render() {
    SDL_RenderCopy(g_renderer, backgroundTexture, nullptr, &backgroundRect);
    // ��ư ������ �߰� ����
}

void Intro::HandleEvents(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;

            if (x >= startButtonRect.x && x <= startButtonRect.x + startButtonRect.w &&
                y >= startButtonRect.y && y <= startButtonRect.y + startButtonRect.h) {
                g_current_game_phase = PHASE_Entrance;
            }
            else if (x >= exitButtonRect.x && x <= exitButtonRect.x + exitButtonRect.w &&
                y >= exitButtonRect.y && y <= exitButtonRect.y + exitButtonRect.h) {
                g_flag_running = false;
            }
        }
    }
}
