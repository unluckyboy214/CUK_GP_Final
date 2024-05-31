// K_NPC.h
#ifndef K_NPC_H
#define K_NPC_H

#include "NPC.h"

class K_NPC : public NPC {
public:
    K_NPC(SDL_Renderer* renderer, int x, int y);
};

#endif