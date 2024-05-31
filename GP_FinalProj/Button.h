// Button.h
#pragma once
#include <SDL.h>

class Button {
public:
    Button(int x, int y, int width, int height, const char* imagePath);
    ~Button();

    void Render();
    bool IsClicked(int mouseX, int mouseY);

private:
    SDL_Rect rect_;
    SDL_Texture* texture_;
};