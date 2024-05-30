// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <vector>
#include "Monster.h"

class Monster;

class Player {
public:
    Player();
    void Update(float deltaTime);
    void Render();
    void HandleEvents(const SDL_Event& event, const std::vector<Monster*>& monsters); // 몬스터 목록을 인자로 받도록 수정
    void PerformParry(const std::vector<Monster*>& monsters); // 몬스터 목록을 인자로 받도록 수정
    void SetParrying(bool parrying);
    bool IsParrying() const;
    const SDL_Rect& GetRect() const;

private:
    SDL_Texture* texture_;
    SDL_Rect rect_;
    bool is_parrying_;
    float move_speed_;
    float parry_cooldown_;
    float parry_duration_;
    float parry_timer_;
    int direction_;
};

#endif // PLAYER_H