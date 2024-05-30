// Entrance.h
#pragma once
#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Map.h"
#include "K_Npc.h"
#include "ScriptWindow.h"

class Entrance : public Map {
public:
    Entrance();
    void SpawnNPC();
    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvents() override;
    void SpawnMonsters() override;
    void TransitionToNextMap() override;

private:
    K_Npc* npc;
    ScriptWindow* scriptWindow;
};

#endif