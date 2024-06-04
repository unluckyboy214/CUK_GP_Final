#ifndef NICOLS1_H
#define NICOLS1_H

#include "Map.h"

class Nicols1 : public Map {
public:
    Nicols1();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
private:
    int deathCount; // 몬스터가 죽은 횟수를 추적
};

#endif // NICOLS1_H
