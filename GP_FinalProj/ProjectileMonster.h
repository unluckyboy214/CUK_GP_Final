// ProjectileMonster.h
#ifndef PROJECTILEMONSTER_H
#define PROJECTILEMONSTER_H
#include "Monster.h"
class ProjectileMonster : public Monster {
public:
    ProjectileMonster(int x, int y, float velX, float velY);
    void Update(float deltaTime);  // 함수 선언 수정
    bool IsOutOfBounds() const;

private:
    float velX;
    float velY;
};
#endif // PROJECTILEMONSTER_H