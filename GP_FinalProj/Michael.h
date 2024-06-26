#ifndef MICHAEL_H
#define MICHAEL_H

#include "Map.h"

class Michael : public Map {
public:
    Michael();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
private:
    int deathCount;
};

#endif // MICHAEL_H
