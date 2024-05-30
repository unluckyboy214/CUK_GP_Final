#pragma once
#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Map.h"
#include "K_Npc.h"



class Entrance : public Map {
public:
    Entrance();
    void SpawnMonsters() override;

private:
    K_Npc* npc;  // NPC ��ü
};


#endif