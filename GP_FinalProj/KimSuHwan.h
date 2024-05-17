// Kimsuhwan.h
#pragma once

#include "SDL.h"
#include "Monster.h"

class KimSuHwan
{
public:
    KimSuHwan();
    ~KimSuHwan();

    void HandleEvents();
    void Update(float deltaTime);
    void Render();

private:
    // 이미지 관련
    SDL_Texture* texture_; // the SDL_Texture 
    SDL_Rect source_rectangle_; // the rectangle for source image
    SDL_Rect destination_rectangle_; // for destination
    SDL_Texture* g_flight_sheet_texture_up;
    SDL_Texture* g_flight_sheet_texture_down;
    SDL_Texture* g_flight_sheet_texture_left;
    SDL_Texture* g_flight_sheet_texture_right;

    // 포탈 관련
    SDL_Texture* portal_texture;
    SDL_Rect portal_rect_KtoE;
    SDL_Rect portal_rect_KtoH;

    // 몬스터 관련
    Monster* monster;
    void SpawnMonster();

    // 클로킹 관련
    bool is_cloaking;
    int cloaking_alpha;
    bool is_cloaking_on;
    float cloaking_time;
    float cloaking_duration;

};