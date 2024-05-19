#ifndef FOLLOWINGMONSTER_H
#define FOLLOWINGMONSTER_H

#include "Monster.h"

class FollowingMonster : public Monster {
public:
    FollowingMonster(int x, int y);
    void Update(int playerX, int playerY) override; // override 지시자 사용
};

#endif
