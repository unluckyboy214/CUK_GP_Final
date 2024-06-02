#ifndef NICOLS1_H
#define NICOLS1_H

#include "Map.h"

class Nicols1 : public Map {
public:
    Nicols1();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
};

#endif // NICOLS1_H
