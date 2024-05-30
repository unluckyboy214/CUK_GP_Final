#pragma once
#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <vector>
#include "Monster.h"
#include "Player.h"

class Map {
public:
    Map(const char* backgroundPath, const SDL_Rect& portalRect);
    virtual ~Map();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void HandleEvents();
    virtual void SpawnMonsters() = 0; // ���� ���� �Լ�
    const std::vector<Monster*>& GetMonsters() const;

protected:
    SDL_Texture* texture_;
    SDL_Texture* portal_texture;
    SDL_Rect source_rectangle_;
    SDL_Rect destination_rectangle_;
    SDL_Rect portal_rect_;
    std::vector<Monster*> monsters;
    Player player_;

    void LoadBackground(const char* path);
    void LoadPortal();
    void ResetMonsters();
};

#endif // MAP_H
