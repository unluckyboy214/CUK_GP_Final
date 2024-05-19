#ifndef STATICMONSTER_H
#define STATICMONSTER_H

#include "Monster.h"

class StaticMonster : public Monster {
public:
    StaticMonster(int x, int y);
    void Update(int playerX, int playerY) override; // override 지시자 사용
};

#endif
