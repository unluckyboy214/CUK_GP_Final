#include "E_NPC.h"

E_NPC::E_NPC(SDL_Renderer* renderer, int x, int y)
    : NPC(renderer, "../../Resource/Npc/NPC.png", x, y) {
    setSize(50, 50);  // �̹��� ũ�⸦ 50x50���� ����
}