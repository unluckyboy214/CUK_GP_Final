#ifndef NPC_H
#define NPC_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Player.h"

class NPC {
public:
    NPC(const char* texturePath, int x, int y, SDL_Renderer* renderer, TTF_Font* font);
    virtual ~NPC();
    virtual void Interact(Player& player, SDL_Renderer* renderer);
    virtual void Render(SDL_Renderer* renderer);

protected:
    SDL_Texture* texture_;
    SDL_Rect rect_;
    std::string dialogue_;
    bool isInteracting_;
    TTF_Font* font_;

    void LoadTexture(const char* path, SDL_Renderer* renderer);
    void ShowDialogue(SDL_Renderer* renderer);
};

#endif // NPC_H
