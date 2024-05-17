// Dasol.h
#pragma once

#include "SDL.h"

class Dasol
{
public:
    Dasol();
    ~Dasol();

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
    SDL_Rect portal_rect_DtoB;
    SDL_Rect portal_rect_DtoS;
};