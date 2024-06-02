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
    void SpawnMonster() override;

private:
    std::vector<SDL_Texture*> bossIntroFrames; // 보스 인트로 프레임들
    BossMonster* bossMonster;
    bool showBossIntro;
    float bossIntroTotalTimer;
    float frameTimer;
    float frameDuration;
    int currentFrame;
    void RenderBossHP(); // 보스 HP 렌더링 함수
};
