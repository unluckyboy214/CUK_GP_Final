#pragma once

#include "SDL.h"

class RangedMonster;

class Nicols1
{
public:
    Nicols1();
    ~Nicols1();

    void HandleEvents();
    void Update(float deltaTime);
    void Render();

private:
    // �̹��� ����
    SDL_Texture* texture_; // the SDL_Texture 
    SDL_Rect source_rectangle_; // the rectangle for source image
    SDL_Rect destination_rectangle_; // for destination
    SDL_Texture* g_flight_sheet_texture_up;
    SDL_Texture* g_flight_sheet_texture_down;
    SDL_Texture* g_flight_sheet_texture_left;
    SDL_Texture* g_flight_sheet_texture_right;

    // ��Ż ����
    SDL_Texture* portal_texture;
    SDL_Rect portal_rect_N1toH;
    SDL_Rect portal_rect_N1toN2;
    SDL_Rect portal_rect_N1toV;

    // ���� ����
    SDL_Texture* rock_texture;
    SDL_Rect rockRect;

    // ���� ����
    RangedMonster* rangedMonster;

    void SpawnMonsters();
};
