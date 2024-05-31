#include "E_NPC.h"

E_NPC::E_NPC(SDL_Renderer* renderer, int x, int y)
    : NPC(renderer, "../../Resource/Npc/NPC.png", x, y) {
    setSize(50, 50);  // 이미지 크기를 50x50으로 설정
}