#include "K_NPC.h"

K_NPC::K_NPC(SDL_Renderer* renderer, int x, int y)
    : NPC(renderer, "../../Resource/Npc/Statue.png", x, y) {
    setSize(50, 50);  // �̹��� ũ�⸦ 50x50���� ����
}