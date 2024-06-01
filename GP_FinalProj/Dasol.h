#ifndef DASOL_H
#define DASOL_H

#include "Map.h"

class Dasol : public Map {
public:
    Dasol();
    void SpawnMonsters() override;
    void SpawnMonster();
};

#endif // DASOL_H
