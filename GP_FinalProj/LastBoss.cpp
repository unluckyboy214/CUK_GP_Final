#include "GameClass.h"
#include "LastBoss.h"
#include "BossMonster.h"
#include <SDL_image.h>

LastBoss::LastBoss()
    : Map("../../Resource/Map/LastBoss.png", { (WINDOW_WIDTH - 100) / 2, 0, 100, 100 }), showBossIntro(true), bossIntroTotalTimer(4.0f), currentFrame(0), frameDuration(1.0f), frameTimer(0.0f), bossMonster(nullptr) {
    SpawnMonsters();

    // ���� ��Ʈ�� ������ �ε� (����: 4 ������)
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
    int bossY = 0; // ���� ���� ����
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

    Map::Update(deltaTime); // �⺻ �� ������Ʈ ȣ��
}

void LastBoss::Render() {
    if (showBossIntro) {
        SDL_RenderCopy(g_renderer, bossIntroFrames[currentFrame], NULL, &destination_rectangle_);
        SDL_RenderPresent(g_renderer);
        return;
    }

    Map::Render(); // �⺻ �� ���� ȣ��

    // ���� HP ǥ��
    if (bossMonster) {
        RenderBossHP();
    }
}

void LastBoss::RenderBossHP() {
    int bossHP = bossMonster->getHP();
    int maxHP = 20; // �ִ� HP ����

    // HP �� ���
    SDL_Rect hpBarBg = { (WINDOW_WIDTH - 400) / 2, 20, 400, 40 };
    SDL_SetRenderDrawColor(g_renderer, 50, 50, 50, 255); // £�� ȸ��
    SDL_RenderFillRect(g_renderer, &hpBarBg);

    // ���� HP ��
    SDL_Rect hpBarValue = { (WINDOW_WIDTH - 400) / 2, 20, 400 * bossHP / maxHP, 40 };
    SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255); // ���� ��
    SDL_RenderFillRect(g_renderer, &hpBarValue);

    // �׵θ�
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255); // ���
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
            return; // ���� ��Ʈ�ΰ� ǥ�õǴ� ���� �ٸ� �̺�Ʈ ó�� ����
        }

        Map::HandleEvents(); // �⺻ �� �̺�Ʈ ó�� ȣ��
    }
}
