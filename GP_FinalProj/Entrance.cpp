#include "GameClass.h"
#include "Entrance.h"
#include <SDL_image.h>
extern SDL_Renderer* g_renderer;
extern TTF_Font* g_font;

Entrance::Entrance()
    : Map("../../Resource/Map/Entrance.png", { (WINDOW_WIDTH - 100) / 2, 50, 100, 100 }),
    scriptWindow(nullptr) {
    SpawnNPC();
    scriptWindow = new ScriptWindow();
}

Entrance::~Entrance() {
    delete scriptWindow;
}

void Entrance::SpawnMonsters() {
    // No monsters in the Entrance map
}

void Entrance::SpawnNPC() {
    npc = new E_NPC(g_renderer, 200, 200);
}

void Entrance::Update(float deltaTime) {
    Map::Update(deltaTime);
    SDL_Rect npcRect = npc->getRect();  // npc->rect ��� npc->getRect() ���
    if (npcRect.x <= g_player_destination_rect.x + g_player_destination_rect.w &&
        npcRect.x + npcRect.w >= g_player_destination_rect.x &&
        npcRect.y <= g_player_destination_rect.y + g_player_destination_rect.h &&
        npcRect.y + npcRect.h >= g_player_destination_rect.y) {
        // NPC�� �÷��̾ �浹�� ��쿡 ���� ó��
        // ��: ��ȭ ���� ǥ�� ��
    }
}

void Entrance::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            // ���� Ű �Է� �� ��ȭ ���� ó��
            scriptWindow->HandleInput(event);
        }
    }
}

void Entrance::Render() {
    Map::Render();
    npc->render(g_renderer);
    scriptWindow->Render();
}

void Entrance::TransitionToNextMap() {
    g_current_game_phase = PHASE_KimSuHwan;
}