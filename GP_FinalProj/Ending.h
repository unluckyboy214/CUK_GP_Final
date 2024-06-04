#pragma once
#ifndef ENDING_H
#define ENDING_H

#include <SDL.h>

class Ending {
public:
    Ending();
    ~Ending();

    void Update(float deltaTime);
    void Render();

private:
    SDL_Texture* backgroundTexture;
    SDL_Rect backgroundRect;
};

#endif // ENDING_H
