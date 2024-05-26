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
    SDL_Rect rect_;
    SDL_Texture* texture_;
    bool is_parrying_;
    float move_speed_;
};

#endif // PLAYER_H
