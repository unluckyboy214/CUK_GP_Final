// ScriptWindow.h
#pragma once
#ifndef SCRIPT_WINDOW_H
#define SCRIPT_WINDOW_H
#include <SDL.h>
#include <vector>
#include <string>
class ScriptWindow {
public:
    ScriptWindow();
    ~ScriptWindow();
    void Show();
    void Hide();
    void HandleInput(const SDL_Event& event);
    void Render();
    bool IsScriptFinished() const;
    bool IsVisible() const;
private:
    bool isVisible_;
    int currentScriptIndex_;
    std::vector<SDL_Texture*> scriptTextures_;
    bool isScriptFinished_;
};
#endif