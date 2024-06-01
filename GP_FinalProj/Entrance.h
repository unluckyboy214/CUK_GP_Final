#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Map.h"

class Entrance : public Map {
public:
    Entrance();
    void SpawnMonsters() override;
    void SpawnMonster();  // 새로운 몬스터 생성 함수
};

#endif // ENTRANCE_H
