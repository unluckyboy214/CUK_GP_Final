#ifndef SOPHIEBARA_H
#define SOPHIEBARA_H

#include "Map.h"

class Sophiebara : public Map {
public:
    Sophiebara();
    void SpawnMonsters() override;
    void SpawnMonster();
};

#endif // SOPHIEBARA_H
