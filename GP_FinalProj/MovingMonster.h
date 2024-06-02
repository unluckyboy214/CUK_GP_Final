#ifndef MOVINGMONSTER_H
#define MOVINGMONSTER_H

#include "Monster.h"

class MovingMonster : public Monster {
public:
    MovingMonster(int x, int y);

    void Update(float deltaTime, const SDL_Rect& playerRect) override;
    void ParryEffect(const SDL_Rect& playerRect);
    void TakeDamage(int damage);

private:
    void MoveTowardsPlayer(float deltaTime, const SDL_Rect& playerRect);
    void Render();
    int health;
    std::vector<std::string> normalFrameFiles;
    std::vector<std::string> stunFrameFiles;
    bool isStunned;
    bool facingRight;  // Add this variable to track the facing direction
};

#endif // MOVINGMONSTER_H
