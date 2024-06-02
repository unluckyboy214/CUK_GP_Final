#ifndef KIMSUHWAN_H
#define KIMSUHWAN_H

#include "Map.h"

class KimSuHwan : public Map {
public:
    KimSuHwan();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
};

#endif // KIMSUHWAN_H
