// K_Npc.h
#ifndef K_NPC_H
#define K_NPC_H

#include <SDL.h>

class K_Npc {
public:
    K_Npc(const char* texturePath, int x, int y, int width, int height, SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
    bool CheckCollision(const SDL_Rect& playerRect);
    // Other NPC related methods and properties
private:
    SDL_Rect m_rect;
    SDL_Texture* m_texture;
    // Other NPC related properties
};

#endif