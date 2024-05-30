// KimSuHwan.h
#ifndef KIMSUHWAN_H
#define KIMSUHWAN_H

#include "Map.h"
#include "K_Npc.h"


class KimSuHwan : public Map {
public:
    KimSuHwan();
    void SpawnMonsters() override;
    void TransitionToNextMap() override;

private:
    K_Npc* npc;  // NPC ��ü
};


#endif
