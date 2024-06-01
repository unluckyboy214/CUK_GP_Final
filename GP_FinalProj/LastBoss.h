#pragma once
#include "Map.h"
#include "BossMonster.h"
#include <vector>
#include <SDL.h>

class LastBoss : public Map {
public:
    LastBoss();
    ~LastBoss();
    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvents() override;
    void SpawnMonsters() override;

private:
    std::vector<SDL_Texture*> bossIntroFrames; // 보스전 인트로 프레임
    BossMonster* bossMonster;
    bool showBossIntro;
    float bossIntroTotalTimer;
    float frameTimer;
    float frameDuration;
    int currentFrame;
    void RenderBossHP(); // 보스 HP 렌더링 함수
};
