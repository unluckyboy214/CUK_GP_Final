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
    std::vector<SDL_Texture*> bossIntroFrames; // ������ ��Ʈ�� ������
    BossMonster* bossMonster;
    bool showBossIntro;
    float bossIntroTotalTimer;
    float frameTimer;
    float frameDuration;
    int currentFrame;
    void RenderBossHP(); // ���� HP ������ �Լ�
};
