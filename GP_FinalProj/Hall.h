#ifndef HALL_H
#define HALL_H

#include "Map.h"
#include "ChargingMonster.h"

class Hall : public Map {
public:
    Hall();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
};

#endif // HALL_H
