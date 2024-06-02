#ifndef CHARGINGMONSTER_H
#define CHARGINGMONSTER_H

#include "Monster.h"
#include <vector>
#include <SDL.h>

class ChargingMonster : public Monster {
public:
    ChargingMonster(int x, int y);
    void Update(float deltaTime, const SDL_Rect& playerRect) override;
    void Render() override;

private:
    enum State {
        Idle,
        Charging,
        Running,
        Stunned
    } state;

    int health;
    float stateTimer;
    int targetX, targetY;
    float directionX, directionY; // 방향 벡터 추가
    int currentFrame;
    float animationTime;
    float animationSpeed;

    std::vector<SDL_Texture*> idleTextures;
    std::vector<SDL_Texture*> chargingTextures;
    std::vector<SDL_Texture*> runningTextures;
    std::vector<SDL_Texture*> stunnedTexture;

    void LoadTextures();
    void AdvanceFrame(float deltaTime);
    void UpdateState(float deltaTime, const SDL_Rect& playerRect);
    void ResetStateTimer(float time);
    void ChargeTowardsPlayer(float deltaTime);
};

#endif // CHARGINGMONSTER_H
