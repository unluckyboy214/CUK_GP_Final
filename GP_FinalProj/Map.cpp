#include "Map.h"
#include "globals.h"
#include "Entrance.h"
#include "MovingMonster.h"
#include "RangedMonster.h"
#include "ChargingMonster.h"
#include "Player.h"
#include <random>

Map::Map(const char* backgroundPath, int maxMonsters)
    : destination_rectangle_{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT },
    spawnTimer(0.0f),
    spawnDelay(5.0f),
    monstersSpawned(false),
    maxMonsters(maxMonsters) {
    LoadBackground(backgroundPath);
}

Map::~Map() {
    if (texture_) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
    for (auto& monster : monsters) {
        delete monster;
        monster = nullptr;
    }
    monsters.clear();
}

void Map::Update(float deltaTime) {
    player_.Update(deltaTime);

    // 몬스터 생성 타이머 업데이트
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnDelay && !monstersSpawned) {
        SpawnMonsters();  // 몬스터 생성
        monstersSpawned = true;  // 몬스터 생성 플래그 설정
    }

    bool allMonstersDefeated = true;
    for (auto it = monsters.begin(); it != monsters.end();) {
        (*it)->Update(deltaTime, player_.GetRect());
        if ((*it)->CheckCollisionWithPlayer(player_.GetRect())) {
            // 플레이어를 접촉 방향으로 밀어내고 체력 감소
            //player_.OnMonsterCollision((*it)->GetRect());
            delete* it;
            it = monsters.erase(it);
        }
        else {
            ++it;
            allMonstersDefeated = false;
        }
    }

    if (allMonstersDefeated && monsters.empty() && monstersSpawned) {
        g_phase_transition_timer = 2.0f;
    }

    // 남아있는 몬스터의 수가 maxMonsters 이하로 떨어지면 새로운 몬스터 생성
    if (monsters.size() < maxMonsters) {
        int spawnCount = maxMonsters - monsters.size();
        for (int i = 0; i < spawnCount; ++i) {
            SpawnMonster();
        }
    }
}

void Map::Render() {
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, texture_, NULL, &destination_rectangle_);
    for (auto monster : monsters) {
        monster->Render();
    }
    //player_.Render();
}

void Map::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            g_flag_running = false;
        }
        player_.HandleEvents(event, monsters); // 플레이어 이벤트 처리 추가
    }
}

void Map::ResetMonsters() {
    for (auto& monster : monsters) {
        delete monster;
        monster = nullptr;
    }
    monsters.clear();
    monstersSpawned = false;  // 리셋 시 몬스터 생성 플래그 초기화
    spawnTimer = 0.0f;  // 타이머 리셋

    // 플레이어 위치 중앙으로 설정
    player_.SetPosition(WINDOW_WIDTH / 2 - player_.GetRect().w / 2, WINDOW_HEIGHT / 2 - player_.GetRect().h / 2);
}

void Map::LoadBackground(const char* path) {
    SDL_Surface* temp_surface = IMG_Load(path);
    texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
    destination_rectangle_ = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

void Map::SpawnMonsters() {
    // 기본적으로 아무것도 하지 않음. 각 파생 클래스에서 이 함수를 구현해야 함.
}