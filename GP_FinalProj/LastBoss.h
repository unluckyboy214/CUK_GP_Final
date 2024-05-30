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
    void TransitionToNextMap() override;
    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvents() override;

    bool showBossIntro; // public���� �����Ͽ� �ܺο��� ���� �����ϰ� ��

private:
    float bossIntroTotalTimer;
    std::vector<SDL_Texture*> bossIntroFrames; // ���� ��Ʈ�� ������
    int currentFrame;
    float frameDuration;
    float frameTimer;
    BossMonster* bossMonster;
    SDL_Texture* bossHPBarTexture; // ���� HP �� �ؽ�ó

    void RenderBossHP(); // ���� HP �� ������ �Լ�
};

#endif
