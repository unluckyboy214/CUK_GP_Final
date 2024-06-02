#pragma once
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>

class Gameover {
public:
    Gameover();
    ~Gameover();

    void Update(float deltaTime);
    void Render();
    void HandleEvents(SDL_Event& event);

private:
    SDL_Texture* backgroundTexture;
    SDL_Rect backgroundRect;
    SDL_Rect startButtonRect;
    SDL_Rect exitButtonRect;
};

#endif // GAMEOVER_H