#include "globals.h"

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
bool g_flag_running = true;
Uint32 g_last_time_ms = 0;
Uint32 g_frame_per_sec = 30;
int g_current_game_phase = 0;
int g_player_health = 5;
float g_phase_transition_timer = 0.0f;
const int NUMBER_OF_PHASES = 8;  // ������ �� ����
std::vector<SDL_Rect> g_obstacles;
int g_kill_count = 0;
TTF_Font* g_font = nullptr;
int g_paused_game_phase = -1;
bool g_reset_game = false;
bool g_is_fading = false;
int g_fade_alpha = 255;