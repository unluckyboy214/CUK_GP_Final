// ScriptWindow.cpp
#include "ScriptWindow.h"
#include "GameClass.h"
#include <SDL_image.h>

ScriptWindow::ScriptWindow()
    : isVisible_(false), currentScriptIndex_(0), isScriptFinished_(false) {
    scriptTextures_.push_back(IMG_LoadTexture(g_renderer, "../../Resource/Script/script1.png"));
    scriptTextures_.push_back(IMG_LoadTexture(g_renderer, "../../Resource/Script/script2.png"));
    scriptTextures_.push_back(IMG_LoadTexture(g_renderer, "../../Resource/Script/script3.png"));

    for (const auto& texture : scriptTextures_) {
        if (texture == nullptr) {
            // 텍스처 로딩 실패 처리
            std::cout << "Failed to load script texture!" << std::endl;
        }
    }
}

ScriptWindow::~ScriptWindow() {
    for (auto texture : scriptTextures_) {
        SDL_DestroyTexture(texture);
    }
}

void ScriptWindow::Show() {
    isVisible_ = true;
    currentScriptIndex_ = 0;
    isScriptFinished_ = false;
}

void ScriptWindow::Hide() {
    isVisible_ = false;
}

void ScriptWindow::HandleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
        if (currentScriptIndex_ < scriptTextures_.size() - 1) {
            currentScriptIndex_++;
        }
        else {
            Hide();
            isScriptFinished_ = true;
        }
    }
}

void ScriptWindow::Render() {
    if (isVisible_ && currentScriptIndex_ >= 0 && currentScriptIndex_ < scriptTextures_.size()) {
        SDL_Rect scriptRect = { 0, WINDOW_HEIGHT - 200, WINDOW_WIDTH, 200 };
        SDL_RenderCopy(g_renderer, scriptTextures_[currentScriptIndex_], NULL, &scriptRect);
    }
}

bool ScriptWindow::IsScriptFinished() const {
    return isScriptFinished_;
}

bool ScriptWindow::IsVisible() const {
    return isVisible_;
}