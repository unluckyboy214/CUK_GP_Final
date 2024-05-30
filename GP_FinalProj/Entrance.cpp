// Entrance.cpp
#include "GameClass.h"
#include "Entrance.h"
#include <SDL_image.h>

extern SDL_Renderer* g_renderer;
extern TTF_Font* g_font;

Entrance::Entrance()
    : Map("../../Resource/Map/Entrance.png", { (WINDOW_WIDTH - 100) / 2, 50, 100, 100 }) {
    SpawnNPC();
    scriptWindow = new ScriptWindow();
}

void Entrance::SpawnMonsters() {
    // No monsters in the Entrance map
}

void Entrance::SpawnNPC() {
    npc = new K_Npc("../../Resource/Npc/Angel_statue.png", 200, 200, 64, 64, g_renderer);
}

void Entrance::Update(float deltaTime) {
    Map::Update(deltaTime);
    if (npc->CheckCollision(g_player_destination_rect)) {
        if (!scriptWindow->IsScriptFinished()) {
            scriptWindow->Show();
        }
        else {
            scriptWindow->Show();
        }
    }
}

void Entrance::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            if (!scriptWindow->IsScriptFinished()) {
                scriptWindow->HandleInput(event);
            }
        }
    }
}

void Entrance::Render() {
    Map::Render();
    npc->Render(g_renderer);
    scriptWindow->Render();
}

void Entrance::TransitionToNextMap() {
    g_current_game_phase = PHASE_KimSuHwan;
}