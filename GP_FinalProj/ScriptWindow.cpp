// ScriptWindow.cpp
#include "ScriptWindow.h"
#include "GameClass.h"
#include <SDL_ttf.h>
ScriptWindow::ScriptWindow()
    : isVisible_(false), currentScriptIndex_(0), isScriptFinished_(false) {
    scripts_.push_back("hello");
    scripts_.push_back("who are you");
    scripts_.push_back("start");
    scripts_.push_back("go");

    font_ = TTF_OpenFont("../../Resource/YEONGJUSeonbi.ttf", 24);
    if (font_ == nullptr) {
        // 폰트 로드 실패 처리
    }
}

ScriptWindow::~ScriptWindow() {
    TTF_CloseFont(font_);
}

void ScriptWindow::Show() {
    isVisible_ = true;
    currentScriptIndex_ = 0;
    isScriptFinished_ = false;
}

void ScriptWindow::HandleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
        if (currentScriptIndex_ < scripts_.size() - 1) {
            currentScriptIndex_++;
        }
        else {
            isVisible_ = false;
            isScriptFinished_ = true;
        }
    }
}

void ScriptWindow::Render() {
    if (isVisible_) {
        SDL_Rect dialogueRect = { 0, WINDOW_HEIGHT - 150, WINDOW_WIDTH, 150 };
        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 128);
        SDL_RenderFillRect(g_renderer, &dialogueRect);
        SDL_Color color = { 255, 255, 255 };
        SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font_, scripts_[currentScriptIndex_].c_str(), color);
        SDL_Texture* message = SDL_CreateTextureFromSurface(g_renderer, surfaceMessage);
        SDL_Rect messageRect = { 10, WINDOW_HEIGHT - 140, surfaceMessage->w, surfaceMessage->h };
        SDL_RenderCopy(g_renderer, message, NULL, &messageRect);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
    }
}

bool ScriptWindow::IsScriptFinished() const {
    return isScriptFinished_;
}
