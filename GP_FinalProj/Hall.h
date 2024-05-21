#ifndef HALL_H
#define HALL_H

#include <SDL.h>
#include <vector>
#include "Monster.h"

class Hall {
public:
    Hall();
    ~Hall();
    void Update(float deltaTime);
    void Render();
    void HandleEvents();

private:
    SDL_Texture* texture_;
    SDL_Rect source_rectangle_;
    SDL_Rect destination_rectangle_;
    SDL_Texture* g_flight_sheet_texture;
    SDL_Texture* portal_texture;
    SDL_Rect portal_rect_HtoK;
    SDL_Rect portal_rect_HtoN1;

    std::vector<Monster*> monsters;

    void SpawnMonsters();
    void ResetMonsters();
};

#endif // HALL_H
