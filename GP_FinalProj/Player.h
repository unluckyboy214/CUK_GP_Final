#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "Monster.h"
#include "GameClass.h"

class Monster;

enum class PlayerState {
    Idle,
    Move,
    Parry,
    Damage,
    Death
};

struct Animation {
    std::vector<SDL_Texture*> frames;
    float frame_duration;  // 각 프레임의 지속 시간
};

class Player {
public:
    Player();
    void Update(float deltaTime);
    void Render();
    void HandleEvents(const SDL_Event& event, std::vector<Monster*>& monsters);
    void PerformParry( std::vector<Monster*>& monsters);
    void SetParrying(bool parrying);
    bool IsParrying() const;
    SDL_Rect GetRect() const;
    void SetPosition(int x, int y);

private:
    void LoadTextures();
    void LoadAnimation(PlayerState state, const std::string& base_path, int frame_count, float frame_duration);

    SDL_Rect rect_;
    bool is_parrying_;
    float move_speed_;
    float parry_cooldown_;
    float parry_duration_;
    float parry_timer_;
    int direction_;
    PlayerState state_;
    PlayerState prev_state_;  // 이전 상태를 저장
    int current_frame_;
    float frame_time_;
    bool flip_;  // 캐릭터 이미지 반전 여부

    std::unordered_map<PlayerState, Animation> animations_;
    static bool textures_loaded_;  // 플래그 추가
    static std::unordered_map<PlayerState, Animation> shared_animations_;  // 공유 애니메이션 추가
};

#endif // PLAYER_H
