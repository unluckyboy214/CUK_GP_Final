#ifndef RANGEDMONSTER_H
#define RANGEDMONSTER_H

#include "Monster.h"
#include <vector>
#include <SDL.h>

struct Projectile {
    SDL_Rect rect;
    float velX;
    float velY;
    bool active;
};

class RangedMonster : public Monster {
public:
    RangedMonster(int x, int y);
    void Update(float deltaTime, const SDL_Rect& playerRect) override;
    void Render() override;
    void ShootProjectile(const SDL_Rect& playerRect);
    std::vector<Projectile>& GetProjectiles(); // Add this line

private:
    float shootCooldown;
    float shootTimer;
    std::vector<Projectile> projectiles;
};

#endif // RANGEDMONSTER_H
