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

protected:
    int x;
    int y;
    int health;
    std::vector<SDL_Texture*> textures; // Vector to store animation frames
    int currentFrame;
    float animationTime;
    float animationSpeed;

    void LoadTextures(const std::vector<std::string>& frameFiles); // Function to load textures
    void AdvanceFrame(float deltaTime); // Function to advance animation frame
};

#endif // MONSTER_H
