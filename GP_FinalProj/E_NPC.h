// E_NPC.h
#ifndef E_NPC_H
#define E_NPC_H

#include "NPC.h"

class E_NPC : public NPC {
public:
    E_NPC(SDL_Renderer* renderer, int x, int y);
};

#endif