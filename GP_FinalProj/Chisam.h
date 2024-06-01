#ifndef CHISAM_H
#define CHISAM_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>
#include <ctime>

class Chisam {
public:
    Chisam(int mapWidth, int mapHeight, SDL_Renderer* renderer, TTF_Font* font);
    ~Chisam();
    void Render();
    void HandleEvents(SDL_Event& e);
    void GenerateRandomPosition();
    void Update();
    bool IsClicked(int x, int y);

    void SetVisible(bool isVisible);
    bool IsVisible() const;

private:
    SDL_Point position;
    std::vector<std::string> dialogues;
    int currentDialogueIndex;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* texture;
    bool visible;
    int mapWidth, mapHeight;

    void LoadTexture(const char* filePath);

    std::clock_t lastMoveTime;
    double moveInterval;
};

#endif // CHISAM_H
