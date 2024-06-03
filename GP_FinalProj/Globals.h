#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <vector>
#include <SDL_ttf.h>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern bool g_flag_running;
extern Uint32 g_last_time_ms;
extern Uint32 g_frame_per_sec;
extern int g_current_game_phase;
extern int g_player_health;
extern float g_phase_transition_timer;
extern const int NUMBER_OF_PHASES;
extern std::vector<SDL_Rect> g_obstacles;
extern int g_kill_count;
extern TTF_Font* g_font;
extern int g_paused_game_phase;

#endif // GLOBALS_H
