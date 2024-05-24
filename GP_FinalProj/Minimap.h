#pragma once
#include <SDL.h>
#include <vector>

class Minimap {
public:
    Minimap(SDL_Renderer* renderer);
    ~Minimap();

    void Render(int playerX, int playerY);
    void UpdatePlayerPosition(int mapIndex);

private:
    SDL_Renderer* renderer;
    SDL_Texture* mapTexture;
    SDL_Texture* playerTexture;
    SDL_Rect playerRect;
    std::vector<SDL_Rect> mapRects; // ¸Ê À§Ä¡¸¦ ÀúÀåÇÏ´Â º¤ÅÍ
    int currentMapIndex; // ÇöÀç ¸ÊÀÇ ÀÎµ¦½º
};
