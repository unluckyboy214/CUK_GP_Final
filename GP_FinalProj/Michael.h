#ifndef MICHAEL_H
#define MICHAEL_H

#include "Map.h"

class Michael : public Map {
public:
    Michael();
    void SpawnMonsters() override;
    void SpawnMonster();
};

#endif // MICHAEL_H
