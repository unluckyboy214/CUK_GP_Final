#ifndef STATUE_H
#define STATUE_H

#include "NPC.h"

class Statue : public NPC {
public:
    Statue(int x, int y, SDL_Renderer* renderer, TTF_Font* font);
};

#endif // STATUE_H
