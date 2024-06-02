#ifndef MONSTER_H
#define MONSTER_H

#include <SDL.h>
#include <vector>
#include <string>

class Monster {
public:
    Monster(int x, int y);
    virtual ~Monster();
    virtual void Update(float deltaTime, const SDL_Rect& playerRect);
    virtual void Render();
    virtual bool CheckCollisionWithPlayer(const SDL_Rect& playerRect);
    int getX() const;
    int getY() const;
    void SetHealth(int newHealth);
    int GetHealth() const;
    float hitTimer;
    const float hitDuration = 1.5f;
    void RenderHealthBar();  // 체력 바 렌더링 함수 추가
    bool IsDead() const;
    SDL_Rect GetRect() const;  // 추가된 메서드
    Uint32 hitStartTime;

    void SetHitTimer(float duration); // 피격 타이머 설정 함수 추가

protected:
    int x;
    int y;
    int health;
    int maxHealth;  // 최대 체력 변수 추가
    std::vector<SDL_Texture*> textures; // Vector to store animation frames
    int currentFrame;
    float animationTime;
    float animationSpeed;

    void LoadTextures(const std::vector<std::string>& frameFiles); // Function to load textures
    void AdvanceFrame(float deltaTime); // Function to advance animation frame
};

#endif // MONSTER_H
