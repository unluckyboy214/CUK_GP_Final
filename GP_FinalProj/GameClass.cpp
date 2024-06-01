// GameClass.cpp
#include "GameClass.h"
#include "Intro.h"
#include "Entrance.h"
#include "KimSuHwan.h"
#include "Hall.h"
#include "Nicols1.h"
#include "Nicols2.h"
#include "Nicols3.h"
#include "Maria.h"
#include "Virtus.h"
#include "Bambino.h"
#include "Dasol.h"
#include "Michael.h"
#include "LastBoss.h"

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

void InitGame() {
    g_flag_running = true;
    g_current_game_phase = PHASE_Intro; // 추가: 시작 단계를 PHASE_Intro로 설정
    g_player_destination_rect = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100, 100 };
    g_player_direction = PlayerDirection::UP;
}

void ClearGame() {

}