#ifndef KIMSUHWAN_H
#define KIMSUHWAN_H
#include "Map.h"
#include "K_NPC.h"

class KimSuHwan : public Map {
public:
    KimSuHwan();
    void SpawnMonsters() override;
    void SpawnNPC();
    void Update(float deltaTime) override;
    void Render();
    void TransitionToNextMap() override;
private:
    K_NPC* npc;
};
#endif