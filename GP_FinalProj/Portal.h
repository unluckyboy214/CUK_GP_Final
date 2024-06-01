// Portal.h
#pragma once

#include <SDL.h>

class Portal {
public:
    Portal(int x, int y, int dx, int dy);
    void Render() const;
    bool IsColliding(const SDL_Rect& rect) const;
    int GetDX() const;
    int GetDY() const;
    SDL_Texture* GetTexture() const { return texture_; }

private:
    SDL_Rect rect_;
    int dx_;
    int dy_;
    SDL_Texture* texture_;
};