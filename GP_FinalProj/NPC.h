#ifndef NPC_H
#define NPC_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Player;

class NPC {
public:
    NPC(const char* texturePath, int x, int y, SDL_Renderer* renderer, TTF_Font* font);
    ~NPC();

    void Interact(Player& player, SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);

private:
    void LoadTexture(const char* path, SDL_Renderer* renderer);
    void ShowDialogue(SDL_Renderer* renderer);

    SDL_Rect rect_;
    SDL_Texture* texture_;
    bool isInteracting_;
    TTF_Font* font_;
    std::string dialogue_;
};

#endif