// Monster.cpp
#include "Monster.h"
#include "globals.h"
#include <SDL.h>

Monster::Monster(int x, int y) : x(x), y(y) {}

void Monster::Render() {
    // Render the monster at (x, y) position
    SDL_Rect rect = { x, y, 32, 32 }; // Example size of 32x32
    SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255); // Red color for the monster
    SDL_RenderFillRect(g_renderer, &rect);
}

int Monster::getX() const {
    return x;
}

int Monster::getY() const {
    return y;
}
