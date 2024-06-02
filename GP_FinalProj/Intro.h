#pragma once
#include <SDL.h>

class Intro {
public:
    Intro();
    ~Intro();
    void Update(float deltaTime);
    void Render();
    void HandleEvents(SDL_Event& event);

private:
    SDL_Texture* backgroundTexture;
    SDL_Rect backgroundRect;
    SDL_Rect startButtonRect;
    SDL_Rect exitButtonRect;
};
