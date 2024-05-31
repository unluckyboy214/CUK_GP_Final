#ifndef ENTRANCE_H
#define ENTRANCE_H
#include "Map.h"
#include "E_NPC.h"
#include "ScriptWindow.h"

class Entrance : public Map {
public:
    Entrance();
    ~Entrance();
    void SpawnNPC();
    void Update(float deltaTime) override;
    void Render();
    void HandleEvents();
    void SpawnMonsters() override;
    void TransitionToNextMap() override;
private:
    E_NPC* npc;
    ScriptWindow* scriptWindow;
};
#endif