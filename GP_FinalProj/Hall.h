#ifndef HALL_H
#define HALL_H

#include "Map.h"
#include "ChargingMonster.h"

class Hall : public Map {
public:
    Hall();
    void SpawnMonsters() override;
};

#endif // HALL_H
