#ifndef CHISAM_H
#define CHISAM_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>

class Chisam {
public:
    Chisam(int mapWidth, int mapHeight, SDL_Renderer* renderer, TTF_Font* font);
    ~Chisam(); // Destructor to free resources
    void Render();
    void HandleEvents(SDL_Event& e);
    void GenerateRandomPosition();
    bool IsClicked(int x, int y);

    // 접근자 메소드
    void SetVisible(bool isVisible);
    bool IsVisible() const;

private:
    SDL_Point position;
    std::vector<std::string> dialogues;
    int currentDialogueIndex;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* texture; // Texture for Chisam image
    bool visible;
    int mapWidth, mapHeight;

    void LoadTexture(const char* filePath); // Method to load texture
};

#endif
