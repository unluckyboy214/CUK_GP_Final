#include "RangedMonster.h"
#include "globals.h"
#include "GamePhases.h"
#include <cmath>
#include <vector>

RangedMonster::RangedMonster(int x, int y) : Monster(x, y), shootCooldown(1.0f), shootTimer(0.0f) {
    std::vector<std::string> frameFiles = {
        "../../Resource/Monster/shooter_frame1.png",
        "../../Resource/Monster/shooter_frame2.png",
        "../../Resource/Monster/shooter_frame3.png",
        "../../Resource/Monster/shooter_frame4.png",
        "../../Resource/Monster/shooter_frame5.png",
        "../../Resource/Monster/shooter_frame6.png",
        "../../Resource/Monster/shooter_frame7.png",
        "../../Resource/Monster/shooter_frame8.png",
        "../../Resource/Monster/shooter_frame9.png",
        "../../Resource/Monster/shooter_frame10.png",
        "../../Resource/Monster/shooter_frame11.png",
        "../../Resource/Monster/shooter_frame12.png",
        "../../Resource/Monster/shooter_frame13.png",
    };
    LoadTextures(frameFiles);
}

void RangedMonster::Update(float deltaTime, const SDL_Rect& playerRect) {
    AdvanceFrame(deltaTime);
    shootTimer += deltaTime;
    if (shootTimer >= shootCooldown) {
        ShootProjectile(playerRect);
        shootTimer = 0.0f;
    }

    // Update projectile positions and check collisions
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if (it->active) {
            it->rect.x += static_cast<int>(it->velX * deltaTime);
            it->rect.y += static_cast<int>(it->velY * deltaTime);

            // Check if the projectile is out of the screen bounds
            if (it->rect.x < 0 || it->rect.x > WINDOW_WIDTH || it->rect.y < 0 || it->rect.y > WINDOW_HEIGHT) {
                it->active = false;
                it = projectiles.erase(it);
            }
            else {
                // Check collision with the player
                if (SDL_HasIntersection(&it->rect, &playerRect)) {
                    g_player_health--; // Reduce player health
                    it->active = false;
                    it = projectiles.erase(it);

                    // Check if player health is 0
                    if (g_player_health <= 0) {
                        // Reset the game state or set to game over phase
                        g_current_game_phase = PHASE_Entrance; // Or any phase you define for game over
                        g_player_health = 5; // Reset health for new game start
                        break;
                    }
                }
                else {
                    ++it;
                }
            }
        }
        else {
            ++it;
        }
    }
}

void RangedMonster::ShootProjectile(const SDL_Rect& playerRect) {
    float deltaX = playerRect.x - (x + 64);
    float deltaY = playerRect.y - (y + 64);
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance != 0) {
        float velX = deltaX / distance * 200.0f; // Adjust speed as needed
        float velY = deltaY / distance * 200.0f; // Adjust speed as needed

        SDL_Rect projectileRect = { x + 64, y + 64, 16, 16 }; // Initial projectile position and size
        projectiles.push_back({ projectileRect, velX, velY, true });
    }
}

std::vector<Projectile>& RangedMonster::GetProjectiles() {
    return projectiles;
}

void RangedMonster::Render() {
    Monster::Render();

    // Render projectiles
    SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255); // Red color for projectiles
    for (const auto& projectile : projectiles) {
        if (projectile.active) {
            SDL_RenderFillRect(g_renderer, &projectile.rect);
        }
    }
}
