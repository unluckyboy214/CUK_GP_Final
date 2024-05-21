#include "GameClass.h"
#include "Entrance.h"
#include <algorithm>
#include <random>

Entrance::Entrance()
{
    // ��� �ε�
    SDL_Surface* temp_surface = IMG_Load("../../Resource/Map/Entrance.png");
    texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
    destination_rectangle_ = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    // ĳ���� �ε�
    SDL_Surface* flight_sheet_surface = IMG_Load("../../Resource/Character/Isacc.png");
    g_flight_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, flight_sheet_surface);
    SDL_FreeSurface(flight_sheet_surface);

    // ��Ż �ε�
    SDL_Surface* portal_surface = IMG_Load("../../Resource/Map/portal.png");
    SDL_Surface* resized_portal_surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_Rect resized_portal_rect = { 0, 0, 100, 100 };
    SDL_BlitScaled(portal_surface, NULL, resized_portal_surface, &resized_portal_rect);
    SDL_FreeSurface(portal_surface);

    portal_texture = SDL_CreateTextureFromSurface(g_renderer, resized_portal_surface);
    SDL_FreeSurface(resized_portal_surface);

    portal_rect_EtoK = { (WINDOW_WIDTH - 100) / 2, 0, 100, 100 };

    // ���� ����
    SpawnMonster();
}

Entrance::~Entrance()
{
    SDL_DestroyTexture(texture_);
    SDL_DestroyTexture(g_flight_sheet_texture);
    SDL_DestroyTexture(portal_texture);
    if (monster) {
        delete monster;
    }
}

void Entrance::SpawnMonster() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> disX(0, WINDOW_WIDTH);
	std::uniform_int_distribution<> disY(0, WINDOW_HEIGHT);

	int x = disX(gen);
	int y = disY(gen);

	monster = new Monster(x, y);
}

void Entrance::Update(float deltaTime)
{
    const float moveSpeed = 500.0f;

    // �Է� ���¿� ���� �̵�
    if (g_move_left) {
        g_player_destination_rect.x -= moveSpeed * deltaTime;
        g_player_direction = PlayerDirection::LEFT;
    }
    if (g_move_right) {
        g_player_destination_rect.x += moveSpeed * deltaTime;
        g_player_direction = PlayerDirection::RIGHT;
    }
    if (g_move_up) {
        g_player_destination_rect.y -= moveSpeed * deltaTime;
        g_player_direction = PlayerDirection::UP;
    }
    if (g_move_down) {
        g_player_destination_rect.y += moveSpeed * deltaTime;
        g_player_direction = PlayerDirection::DOWN;
    }

    // ������ ��踦 ����� �ʵ��� ����
    g_player_destination_rect.x = std::max(0, std::min(WINDOW_WIDTH - g_player_destination_rect.w - 40, g_player_destination_rect.x));
    g_player_destination_rect.y = std::max(0, std::min(WINDOW_HEIGHT - g_player_destination_rect.h - 40, g_player_destination_rect.y));

    // ��Ż�� ĳ���� �浹 Ȯ��
    if (SDL_HasIntersection(&g_player_destination_rect, &portal_rect_EtoK))
    {
        g_current_game_phase = PHASE_KimSuHwan;
        g_player_destination_rect = { WINDOW_WIDTH / 2, 400, 100, 100 };
        g_player_direction = PlayerDirection::UP;
    }
}

void Entrance::Render()
{
    SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, 0);
    SDL_RenderClear(g_renderer);

    // ���
    SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

    // �����
    SDL_Rect flightRect = g_player_destination_rect;
    SDL_RenderCopy(g_renderer, g_flight_sheet_texture, NULL, &flightRect);

    // ��Ż �׸���
    SDL_RenderCopy(g_renderer, portal_texture, NULL, &portal_rect_EtoK);

    // ���� �׸���
    if (monster) {
        monster->Render();
    }

    SDL_RenderPresent(g_renderer);
}

void Entrance::HandleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                g_move_left = true;
                break;
            case SDLK_RIGHT:
                g_move_right = true;
                break;
            case SDLK_UP:
                g_move_up = true;
                break;
            case SDLK_DOWN:
                g_move_down = true;
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                g_move_left = false;
                break;
            case SDLK_RIGHT:
                g_move_right = false;
                break;
            case SDLK_UP:
                g_move_up = false;
                break;
            case SDLK_DOWN:
                g_move_down = false;
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_RIGHT) {
                g_current_game_phase = PHASE_KimSuHwan;
            }
            break;
        }
    }
}