#include "Chisam.h"
#include <cstdlib>
#include <ctime>
#include <SDL_image.h> // Include SDL_image for loading images

// External global variables
extern int g_current_game_phase;
extern const int PHASE_LastBoss;

Chisam::Chisam(int mapWidth, int mapHeight, SDL_Renderer* renderer, TTF_Font* font)
    : mapWidth(mapWidth), mapHeight(mapHeight), renderer(renderer), font(font), currentDialogueIndex(0), visible(true), texture(nullptr) {
    dialogues = {
        "Hello!", "How are you?", "Nice to meet you!", "Have a good day!",
        "Good luck!", "Keep going!", "Almost there!", "Transitioning to the final map..."
    };
    std::srand(std::time(nullptr));
    GenerateRandomPosition();
    LoadTexture("../../Resource/Chisam.png"); // Load your custom image here
}

Chisam::~Chisam() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Chisam::LoadTexture(const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    if (surface == nullptr) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    }
}

void Chisam::GenerateRandomPosition() {
    // 중앙에 위치하도록 설정
    position.x = mapWidth / 5;
    position.y = mapHeight / 2;
}

void Chisam::Render() {
    if (visible) {
        int characterWidth = 40; // 캐릭터의 너비 (픽셀 단위)
        int characterHeight = 40; // 캐릭터의 높이 (픽셀 단위)

        if (texture) {
            SDL_Rect dstRect = { (position.x * 20) - (characterWidth / 2), (position.y * 20) - (characterHeight / 2), characterWidth, characterHeight }; // 캐릭터 크기 조정
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow for Chisam
            SDL_Rect chisamRect = { position.x * 20, position.y * 20, characterWidth, characterHeight };
            SDL_RenderFillRect(renderer, &chisamRect);
        }

        if (currentDialogueIndex < dialogues.size()) {
            SDL_Color textColor = { 0, 0, 0, 255 };
            SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, dialogues[currentDialogueIndex].c_str(), textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

                // 말풍선 배경을 그리기 위한 사각형
                int padding = 10;
                int bubbleOffsetY = 60; // 말풍선을 위로 올리기 위한 오프셋
                SDL_Rect bgRect = { (position.x * 20) - (textSurface->w / 2) - padding, (position.y * 20) - bubbleOffsetY - padding, textSurface->w + padding * 2, textSurface->h + padding * 2 };

                // 말풍선 배경 색상 설정
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
                SDL_RenderFillRect(renderer, &bgRect);

                // 말풍선 테두리 그리기
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black border
                SDL_RenderDrawRect(renderer, &bgRect);

                // 텍스트 렌더링
                SDL_Rect textRect = { (position.x * 20) - (textSurface->w / 2), (position.y * 20) - bubbleOffsetY, textSurface->w, textSurface->h };
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
            else {
                printf("TTF_RenderUTF8_Solid Error: %s\n", TTF_GetError());
            }
        }
    }
}

void Chisam::HandleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        x /= 20; // Assuming each cell is 20 pixels
        y /= 20;
        if (IsClicked(x, y)) {
            currentDialogueIndex++;
            if (currentDialogueIndex >= dialogues.size()) {
                visible = false;
                // Transition to the last boss map
                g_current_game_phase = PHASE_LastBoss;
            }
        }
    }
}

bool Chisam::IsClicked(int x, int y) {
    return x == position.x && y == position.y;
}

void Chisam::SetVisible(bool isVisible) {
    visible = isVisible;
}

bool Chisam::IsVisible() const {
    return visible;
}