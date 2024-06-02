#ifndef SOPHIEBARA_H
#define SOPHIEBARA_H

#include "Map.h"

class Sophiebara : public Map {
public:
    Sophiebara();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
};

#endif // SOPHIEBARA_H
