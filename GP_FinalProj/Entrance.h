#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Map.h"

class Entrance : public Map {
public:
    Entrance();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
};

#endif // ENTRANCE_H
