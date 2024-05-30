// NPC.h
#ifndef NPC_H
#define NPC_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "ScriptWindow.h"

class NPC {
public:
    NPC(const char* texturePath, int x, int y, SDL_Renderer* renderer, TTF_Font* font);
    ~NPC();
    void Render(SDL_Renderer* renderer);
    bool CheckCollision(const SDL_Rect& playerRect);
    void StartInteraction();
    bool IsInteracting();

private:
    void LoadTexture(const char* path, SDL_Renderer* renderer);

    SDL_Rect rect_;
    SDL_Texture* texture_;
    bool isInteracting_;
    TTF_Font* font_;
    ScriptWindow* scriptWindow_;
};

#endif