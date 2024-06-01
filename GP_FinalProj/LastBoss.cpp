#include "LastBoss.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include <SDL_image.h>
#include <random>

LastBoss::LastBoss() : Map("../../Resource/Map/LastBoss.png"), introTexture_(nullptr), introDisplayed_(false) {
    spawnDelay = 5.0f;
    LoadIntroImage("../../Resource/Intro/LastBossIntro.png");  // 인트로 이미지 로드
}

void LastBoss::LoadIntroImage(const char* path) {
    SDL_Surface* temp_surface = IMG_Load(path);
    introTexture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
}

void LastBoss::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    for (int i = 0; i < 4; ++i) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new MovingMonster(x, y));
    }
    for (int i = 0; i < 3; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new RangedMonster(x, y));
    }
}

void LastBoss::SpawnMonster() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);

    if (monsters.size() < 7) {
        int x = disX(gen);
        int y = disY(gen);
        if (monsters.size() % 2 == 0) {
            monsters.push_back(new MovingMonster(x, y));
        }
        else {
            monsters.push_back(new RangedMonster(x, y));
        }
    }
}

void LastBoss::Render() {
    if (!introDisplayed_ && introTexture_) {
        SDL_RenderCopy(g_renderer, introTexture_, NULL, &destination_rectangle_);
        SDL_RenderPresent(g_renderer);
        SDL_Delay(3000);  // 3초 동안 인트로 이미지 표시
        introDisplayed_ = true;
    }

    // 원래 맵 렌더링
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, texture_, NULL, &destination_rectangle_);
    for (auto monster : monsters) {
        monster->Render();
    }
}
