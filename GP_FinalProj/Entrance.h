#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Map.h"

class Entrance : public Map {
public:
    Entrance();
    void SpawnMonsters() override;
};

#endif // ENTRANCE_H
