// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern bool g_flag_running;
extern Uint32 g_last_time_ms;
extern Uint32 g_frame_per_sec;
extern int g_current_game_phase;
extern int g_player_health; 

#endif // GLOBALS_H
