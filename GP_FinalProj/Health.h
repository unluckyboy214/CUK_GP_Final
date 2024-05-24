#ifndef HEALTH_H
#define HEALTH_H

#include <SDL.h>
#include <vector>
#include <string>
#include <SDL_image.h>

class Health {
public:
    Health(SDL_Renderer* renderer);
    ~Health();
    void Render();
    void Update(int health);

private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> heartTextures;
    SDL_Texture* LoadTexture(const std::string& path);
};

#endif // HEALTH_H
