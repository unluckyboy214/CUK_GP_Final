#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Map.h"

class Tutorial : public Map {
public:
    Tutorial();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
};

#endif // Tutorial_H
