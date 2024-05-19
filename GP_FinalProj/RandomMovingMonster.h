#ifndef RANDOMMOVINGMONSTER_H
#define RANDOMMOVINGMONSTER_H

#include "Monster.h"

class RandomMovingMonster : public Monster {
public:
    RandomMovingMonster(int x, int y);
    void Update(int playerX, int playerY) override; // override 지시자 사용
};

#endif
