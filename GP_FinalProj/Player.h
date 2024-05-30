// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
public:
    Player();
    void Update(float deltaTime);
    void Render();
    void HandleEvents(const SDL_Event& event);
    void SetParrying(bool parrying);
    bool IsParrying() const;
    const SDL_Rect& GetRect() const;

private:
    bool is_parrying_;
    float move_speed_;
    SDL_Texture* texture_;
    SDL_Rect rect_;
    float parry_cooldown_;    // 패링 쿨다운 시간
    float parry_duration_;    // 패링 지속 시간
    float parry_timer_;       // 패링 타이머
    int direction_;           // 플레이어가 바라보는 방향 (0: 상, 1: 우, 2: 하, 3: 좌)

    void UpdateDirection(const SDL_Event& event);
    void PerformParry();
};

#endif // PLAYER_H
