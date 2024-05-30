#include "GameClass.h"
#include "LastBoss.h"
#include "BossMonster.h"
#include <SDL_image.h>

LastBoss::LastBoss()
    : Map("../../Resource/Map/LastBoss.png", { (WINDOW_WIDTH - 100) / 2, 0, 100, 100 }), showBossIntro(true), bossIntroTotalTimer(4.0f), currentFrame(0), frameDuration(1.0f), frameTimer(0.0f), bossMonster(nullptr) {
    SpawnMonsters();

    // 보스 인트로 프레임 로드 (예제: 4 프레임)
    for (int i = 1; i <= 4; ++i) {
        std::string path = "../../Resource/Intro/boss_intro_frame" + std::to_string(i) + ".png";
        SDL_Surface* surface = IMG_Load(path.c_str());
        bossIntroFrames.push_back(SDL_CreateTextureFromSurface(g_renderer, surface));
        SDL_FreeSurface(surface);
    }
}

LastBoss::~LastBoss() {
    for (auto texture : bossIntroFrames) {
        SDL_DestroyTexture(texture);
    }
}

void LastBoss::SpawnMonsters() {
    int bossX = (WINDOW_WIDTH - 128) / 2;
    int bossY = 0; // 맵의 가장 위쪽
    bossMonster = new BossMonster(bossX, bossY);
    monsters.push_back(bossMonster);
}

void LastBoss::Update(float deltaTime) {
    if (showBossIntro) {
        bossIntroTotalTimer -= deltaTime;
        frameTimer += deltaTime;
        if (frameTimer >= frameDuration) {
            frameTimer = 0.0f;
            currentFrame++;
            if (currentFrame >= bossIntroFrames.size()) {
                showBossIntro = false;
                return;
            }
        }
        return;
    }

    Map::Update(deltaTime); // 기본 맵 업데이트 호출
}

void LastBoss::Render() {
    if (showBossIntro) {
        SDL_RenderCopy(g_renderer, bossIntroFrames[currentFrame], NULL, &destination_rectangle_);
        SDL_RenderPresent(g_renderer);
        return;
    }

    Map::Render(); // 기본 맵 렌더 호출

    // 보스 HP 표시
    if (bossMonster) {
        RenderBossHP();
    }
}

void LastBoss::RenderBossHP() {
    int bossHP = bossMonster->getHP();
    int maxHP = 20; // 최대 HP 설정

    // HP 바 배경
    SDL_Rect hpBarBg = { (WINDOW_WIDTH - 400) / 2, 20, 400, 40 };
    SDL_SetRenderDrawColor(g_renderer, 50, 50, 50, 255); // 짙은 회색
    SDL_RenderFillRect(g_renderer, &hpBarBg);

    // 현재 HP 바
    SDL_Rect hpBarValue = { (WINDOW_WIDTH - 400) / 2, 20, 400 * bossHP / maxHP, 40 };
    SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255); // 붉은 색
    SDL_RenderFillRect(g_renderer, &hpBarValue);

    // 테두리
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255); // 흰색
    SDL_RenderDrawRect(g_renderer, &hpBarBg);
}

void LastBoss::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            g_flag_running = false;
        }

        if (showBossIntro) {
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN) {
                frameTimer = 0.0f;
                currentFrame++;
                if (currentFrame >= bossIntroFrames.size()) {
                    showBossIntro = false;
                }
            }
            return; // 보스 인트로가 표시되는 동안 다른 이벤트 처리 중지
        }

        Map::HandleEvents(); // 기본 맵 이벤트 처리 호출
    }
}
