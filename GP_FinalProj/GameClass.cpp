#include "GameClass.h"
#include "Intro.h"
#include "Entrance.h"
#include "KimSuHwan.h"
#include "Hall.h"
#include "Nicols1.h"
#include "Dasol.h"
#include "Sophiebara.h"
#include "Michael.h"
#include "LastBoss.h"
#include "GameOver.h"
#include "Pause.h"
#include "Tutorial.h"

// Game variables
SDL_Rect g_player_destination_rect;
PlayerDirection g_player_direction;
bool is_cloaking;
int cloaking_alpha;
bool is_cloaking_on;
float cloaking_time;
float cloaking_duration;
bool g_move_left = false;
bool g_move_right = false;
bool g_move_up = false;
bool g_move_down = false;

Mix_Music* g_background_music = nullptr;

void InitGame() {
    g_flag_running = true;
    g_current_game_phase = PHASE_Intro;
    g_player_destination_rect = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100, 100 };
    g_player_direction = PlayerDirection::UP;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void ClearGame() {
    if (g_background_music) {
        Mix_FreeMusic(g_background_music);
        g_background_music = nullptr;
    }
    Mix_CloseAudio();
}

void PlayBackgroundMusic(const char* file) {
    if (g_background_music) {
        Mix_FreeMusic(g_background_music);
    }
    g_background_music = Mix_LoadMUS(file);
    if (g_background_music == nullptr) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
    }
    else {
        Mix_PlayMusic(g_background_music, -1);
    }
}

void StopBackgroundMusic() {
    Mix_HaltMusic();
}


