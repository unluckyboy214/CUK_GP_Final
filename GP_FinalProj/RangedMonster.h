#ifndef RANGEDMONSTER_H
#define RANGEDMONSTER_H

#include "Monster.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

struct Projectile {
    SDL_Rect rect;
    float velX;
    float velY;
    bool active;
    SDL_Texture* texture; // Add this to store the projectile texture
};

class RangedMonster : public Monster {
public:
    RangedMonster(int x, int y);
    void Update(float deltaTime, const SDL_Rect& playerRect) override;
    void Render() override;
    void ShootProjectile(const SDL_Rect& playerRect);
    std::vector<Projectile>& GetProjectiles(); // Add this line

private:
    void LoadProjectileTexture(); // Add this method to load projectile texture

    int health;
    float shootCooldown;
    float shootTimer;
    std::vector<Projectile> projectiles;
    bool facingRight; // Add this variable to track the facing direction
    SDL_Texture* projectileTexture; // Add this to store the loaded projectile texture
};

#endif // RANGEDMONSTER_H
