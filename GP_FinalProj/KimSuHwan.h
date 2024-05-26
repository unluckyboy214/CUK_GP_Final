// KimSuHwan.h
#ifndef KIMSUHWAN_H
#define KIMSUHWAN_H

#include <SDL.h>
#include <vector>
#include "Monster.h"
#include "Player.h"

class KimSuHwan {
public:
    KimSuHwan();
    ~KimSuHwan();
    void Update(float deltaTime);
    void Render();
    void HandleEvents();

private:
    void SpawnMonsters();
    void ResetMonsters();

    SDL_Texture* texture_;
    SDL_Texture* portal_texture;
    SDL_Rect source_rectangle_;
    SDL_Rect destination_rectangle_;
    SDL_Rect portal_rect_KtoE;
    SDL_Rect portal_rect_KtoH;
    std::vector<Monster*> monsters;
    Player player_; // Player 객체 추가
};

#endif // KIMSUHWAN_H
