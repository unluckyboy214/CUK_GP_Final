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
        if (texture) {
            SDL_Rect dstRect = { (position.x * 20) - 10, (position.y * 20) - 10, 20, 20 }; // 이미지 크기 조정 필요
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow for Chisam
            SDL_Rect chisamRect = { position.x * 20, position.y * 20, 20, 20 };
            SDL_RenderFillRect(renderer, &chisamRect);
        }

        if (currentDialogueIndex < dialogues.size()) {
            SDL_Color color = { 0, 0, 0, 255 };
            SDL_Surface* surface = TTF_RenderText_Solid(font, dialogues[currentDialogueIndex].c_str(), color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect dstRect = { (position.x * 20) - (surface->w / 2), (position.y * 20) - 30, surface->w, surface->h };
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
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
