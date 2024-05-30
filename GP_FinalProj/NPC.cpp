#include "NPC.h"
#include "GameClass.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

NPC::NPC(const char* texturePath, int x, int y, SDL_Renderer* renderer, TTF_Font* font)
    : rect_{ x, y, 64, 64 }, isInteracting_(false), font_(font) {
    LoadTexture(texturePath, renderer);
}

NPC::~NPC() {
    SDL_DestroyTexture(texture_);
}

void NPC::LoadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* temp_surface = IMG_Load(path);
    texture_ = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
}

void NPC::Interact(Player& player, SDL_Renderer* renderer) {
    isInteracting_ = true;
    ShowDialogue(renderer);
}

void NPC::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture_, NULL, &rect_);
    if (isInteracting_) {
        ShowDialogue(renderer);
    }
}

void NPC::ShowDialogue(SDL_Renderer* renderer) {
    // ������ ������ �ڽ�
    SDL_Rect dialogueRect = { 0, WINDOW_HEIGHT - 150, WINDOW_WIDTH, 150 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, &dialogueRect);

    // �ؽ�Ʈ ������ (��ȭ)
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font_, dialogue_.c_str(), color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect messageRect = { 10, WINDOW_HEIGHT - 140, surfaceMessage->w, surfaceMessage->h };
    SDL_RenderCopy(renderer, message, NULL, &messageRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);

    // NPC Ȯ�� �̹���
    SDL_Rect npcZoomRect = { WINDOW_WIDTH - 110, WINDOW_HEIGHT - 140, 100, 100 };
    SDL_RenderCopy(renderer, texture_, NULL, &npcZoomRect);
}
