#ifndef SOPHIEBARA_H
#define SOPHIEBARA_H

#include "Map.h"

class Sophiebara : public Map {
public:
    Sophiebara();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
private:
    int deathCount;
};

#endif // SOPHIEBARA_H
