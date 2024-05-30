// Entrance.h
#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Map.h"
#include "K_Npc.h"
#include "ScriptWindow.h"

class Entrance : public Map {
public:
    Entrance();
    ~Entrance(); // 소멸자 선언 추가
    void SpawnNPC();
    void Update(float deltaTime) override;
    void Render();
    void HandleEvents();
    void SpawnMonsters() override;
    void TransitionToNextMap() override;

private:
    K_Npc* npc;
    ScriptWindow* scriptWindow;
};

#endif