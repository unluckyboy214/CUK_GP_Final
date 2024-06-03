// Pause.h
#ifndef PAUSE_H
#define PAUSE_H

#include <SDL.h>

class Pause {
public:
    Pause();
    ~Pause();
    void Update(float deltaTime);
    void Render();
    void HandleEvents(SDL_Event& event);
    SDL_Texture* GetBackgroundTexture() const { return backgroundTexture; }

private:
    SDL_Texture* backgroundTexture;
    SDL_Rect backgroundRect;
    SDL_Texture* continueTexture;
    SDL_Rect continueRect;
    SDL_Texture* retryTexture;
    SDL_Rect retryRect;
    SDL_Texture* quitTexture;
    SDL_Rect quitRect;

    void LoadTextures();
};

#endif // PAUSE_H