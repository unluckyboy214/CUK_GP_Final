#ifndef LASTBOSS_H
#define LASTBOSS_H

#include "Map.h"

class LastBoss : public Map {
public:
    LastBoss();
    void SpawnMonsters() override;
    void SpawnMonster();

    // 추가: 인트로 이미지 로드를 위한 함수
    void LoadIntroImage(const char* path);

    void Render() override;  // 추가: 인트로 이미지를 렌더링하기 위해 Render 함수 오버라이드

private:
    SDL_Texture* introTexture_;
    bool introDisplayed_;
};

#endif // LASTBOSS_H
