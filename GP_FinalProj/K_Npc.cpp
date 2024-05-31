#include "K_NPC.h"

K_NPC::K_NPC(SDL_Renderer* renderer, int x, int y)
    : NPC(renderer, "../../Resource/Npc/Statue.png", x, y) {
    setSize(50, 50);  // 이미지 크기를 50x50으로 설정
}