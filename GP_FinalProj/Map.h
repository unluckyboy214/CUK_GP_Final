#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <vector>
#include "Monster.h"
#include "Player.h"
#include <SDL_image.h>
#include "globals.h"

class Map {
public:
    SDL_Texture* texture_;
    SDL_Rect source_rectangle_;
    SDL_Rect destination_rectangle_;
    std::vector<Monster*> monsters;
    void SpawnMonster();
    Player player_;

    float spawnTimer;  // 몬스터 생성 타이머
    float spawnDelay;  // 몬스터 생성 지연 시간
    bool monstersSpawned; // 몬스터가 생성되었는지 여부

    static const int MaxMonsters = 10; // 최대 몬스터 수

    Map(const char* backgroundPath);
    virtual ~Map();

    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void HandleEvents();
    virtual void SpawnMonsters() = 0; // 순수 가상 함수

    void ResetMonsters();
    void LoadBackground(const char* path);

    std::vector<Monster*>& GetMonsters() {
        return monsters;
    }
};

#endif // MAP_H
