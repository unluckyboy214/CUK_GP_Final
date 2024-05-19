//Hall.h
#pragma once

#include "SDL.h"
#include "Monster.h"

class Hall
{
public:
    Hall();
    ~Hall();

    void HandleEvents();
    void Update(float deltaTime);
    void Render();

private:
    // 이미지 관련
    SDL_Texture* texture_;
    SDL_Rect source_rectangle_;
    SDL_Rect destination_rectangle_;
    SDL_Texture* g_flight_sheet_texture;

    // 포탈 관련
    SDL_Texture* portal_texture;
    SDL_Rect portal_rect_HtoK;
    SDL_Rect portal_rect_HtoN1;

    // 몬스터 관련
    Monster* monster;
    void SpawnMonster();
};