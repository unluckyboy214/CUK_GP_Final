#ifndef DASOL_H
#define DASOL_H

#include "Map.h"

class Dasol : public Map {
public:
    Dasol();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
};

#endif // DASOL_H
