// globals.cpp
#include "globals.h"
#include "GamePhases.h"

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
bool g_flag_running = true;
Uint32 g_last_time_ms = 0;
Uint32 g_frame_per_sec = 30;
int g_current_game_phase = PHASE_Entrance;
int g_player_health = 5; 
