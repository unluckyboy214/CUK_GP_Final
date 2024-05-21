#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <SDL.h>

class Monster {
public:
    Monster(int x, int y);
    ~Monster();
    void Update(float deltaTime, const SDL_Rect& playerRect); // Update function with player position
    void Render();
    int getX() const;
    int getY() const;
    bool CheckCollisionWithPlayer(const SDL_Rect& playerRect);

private:
    int x;
    int y;
    int health;
    std::vector<SDL_Texture*> textures; // Vector to store animation frames
    int currentFrame;
    float animationTime;
    float animationSpeed;

    void LoadTextures(); // Function to load textures
    void AdvanceFrame(float deltaTime); // Function to advance animation frame
    void MoveTowardsPlayer(float deltaTime, const SDL_Rect& playerRect); // Function to move towards the player
};

#endif // MONSTER_H
