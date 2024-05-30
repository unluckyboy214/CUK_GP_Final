#pragma once
#ifndef SCRIPT_WINDOW_H
#define SCRIPT_WINDOW_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
class ScriptWindow {
public:
    ScriptWindow();
    ~ScriptWindow();
    void Show();
    void HandleInput(const SDL_Event& event);
    void Render();
    bool IsScriptFinished() const;
private:
    bool isVisible_;
    int currentScriptIndex_;
    std::vector<std::string> scripts_;
    bool isScriptFinished_;
    TTF_Font* font_;
};
#endif