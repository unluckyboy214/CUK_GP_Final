#ifndef KIMSUHWAN_H
#define KIMSUHWAN_H

#include <vector>
#include "Monster.h"

class KimSuHwan {
public:
    KimSuHwan();
    ~KimSuHwan();
    void Update(float deltaTime);
    void Render();
    void HandleEvents();

    void ResetMonsters(); // Add method to reset monsters

private:
    SDL_Texture* texture_;
    SDL_Rect source_rectangle_;
    SDL_Rect destination_rectangle_;
    SDL_Texture* g_flight_sheet_texture;
    SDL_Texture* portal_texture;
    SDL_Rect portal_rect_KtoE;
    SDL_Rect portal_rect_KtoH;
    std::vector<Monster*> monsters; // Vector to store multiple monsters

    void SpawnMonsters();
};

#endif // KIMSUHWAN_H
