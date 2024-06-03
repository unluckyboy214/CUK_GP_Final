#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

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

    Mix_Chunk* successSound; // 성공 효과음
};
