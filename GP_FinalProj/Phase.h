// Phase.h
#pragma once

#include <SDL.h>
#include <vector>
#include "Portal.h"
#include "Monster.h"
#include "Player.h"

class Phase {
public:
    Phase(const char* backgroundPath);
    virtual ~Phase();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void HandleEvents();

protected:
    SDL_Texture* background_texture_;
    SDL_Rect background_rect_;
    std::vector<Portal> portals_;
    std::vector<Monster*> monsters_;
    Player player_;

    void LoadBackground(const char* path);
    void AddPortal(int x, int y, int dx, int dy);
    virtual void SpawnMonsters() = 0;
    void ResetMonsters();
};
