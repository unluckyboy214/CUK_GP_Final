#include "GameClass.h"
#include "KimSuHwan.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include <SDL_image.h>
#include <random>

KimSuHwan::KimSuHwan()
    : Map("../../Resource/Map/KimSuHwan.png", { (WINDOW_WIDTH - 100) / 2, 0, 100, 100 }) {
    SpawnMonsters();
    SpawnNPC();
}

void KimSuHwan::SpawnMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, WINDOW_WIDTH - 128);
    std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT - 128);
    for (int i = 0; i < 4; ++i) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new MovingMonster(x, y));
    }
    for (int i = 0; i < 3; i++) {
        int x = disX(gen);
        int y = disY(gen);
        monsters.push_back(new RangedMonster(x, y));
    }
}

void KimSuHwan::SpawnNPC() {
    npc = new K_NPC(g_renderer, 300, 300);
}

void KimSuHwan::Update(float deltaTime) {
    Map::Update(deltaTime);
    SDL_Rect npcRect = npc->getRect();  // npc->rect 대신 npc->getRect() 사용
    if (npcRect.x <= g_player_destination_rect.x + g_player_destination_rect.w &&
        npcRect.x + npcRect.w >= g_player_destination_rect.x &&
        npcRect.y <= g_player_destination_rect.y + g_player_destination_rect.h &&
        npcRect.y + npcRect.h >= g_player_destination_rect.y) {
        // NPC와 플레이어가 충돌한 경우에 대한 처리
        // 예: 대화 상자 표시 등
    }
}

void KimSuHwan::Render() {
    Map::Render();
}

void KimSuHwan::TransitionToNextMap() {
    g_current_game_phase = PHASE_Hall;
}