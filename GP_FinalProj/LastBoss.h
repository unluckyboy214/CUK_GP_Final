#ifndef LASTBOSS_H
#define LASTBOSS_H

#include "Map.h"
#include "BossMonster.h"
#include <vector>

class LastBoss : public Map {
public:
    LastBoss();
    ~LastBoss();
    void SpawnMonsters() override;
    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvents() override;

    bool showBossIntro; // public으로 변경하여 외부에서 접근 가능하게 함

private:
    float bossIntroTotalTimer;
    std::vector<SDL_Texture*> bossIntroFrames; // 보스 인트로 프레임
    int currentFrame;
    float frameDuration;
    float frameTimer;
    BossMonster* bossMonster;
    SDL_Texture* bossHPBarTexture; // 보스 HP 바 텍스처

    void RenderBossHP(); // 보스 HP 바 렌더링 함수
};

#endif
