#ifndef MOVINGMONSTER_H
#define MOVINGMONSTER_H

#include "Monster.h"

class MovingMonster : public Monster {
public:
    MovingMonster(int x, int y);
    void Update(float deltaTime, const SDL_Rect& playerRect) override;
    void ParryEffect(const SDL_Rect& playerRect);

private:
    void MoveTowardsPlayer(float deltaTime, const SDL_Rect& playerRect);
};

#endif // MOVINGMONSTER_H
