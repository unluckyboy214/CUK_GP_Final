#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>

class NPC {
protected:
    SDL_Texture* texture;
    SDL_Rect rect;

public:
    NPC(SDL_Renderer* renderer, const char* imagePath, int x, int y);
    virtual ~NPC();
    virtual void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const { return rect; }
    void setSize(int width, int height);  // setSize 함수 선언 추가
};

#endif