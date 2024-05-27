#include "Minimap.h"
#include <SDL_image.h>
#include <iostream>

Minimap::Minimap(SDL_Renderer* renderer) : renderer(renderer), currentMapIndex(0) {
    // 맵 텍스처 로드
    SDL_Surface* mapSurface = IMG_Load("../../Resource/Map/minimap.png");
    mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    SDL_FreeSurface(mapSurface);

    // 플레이어 텍스처 로드
    SDL_Surface* playerSurface = IMG_Load("../../Resource/Character/player_icon.png");
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    SDL_FreeSurface(playerSurface);

    // 플레이어 Rect 초기화
    playerRect = { 0, 0, 16, 16 }; // 플레이어 아이콘 크기 설정

    // 미니맵의 각 위치를 저장하는 Rect 초기화
    mapRects.push_back({ 10, 140, 32, 32 }); // 정문 위치
    mapRects.push_back({ 10, 115, 32, 32 }); // 김수환 위치
    mapRects.push_back({ 10, 95, 32, 32 }); // 광장 위치
    mapRects.push_back({ 50, 95, 32, 32 }); // 니콜스1 위치
    mapRects.push_back({ 90, 95, 32, 32 }); // 니콜스2 위치
    mapRects.push_back({ 130, 95, 32, 32 }); // 니콜스3 위치
    mapRects.push_back({ 130, 115, 32, 32 }); // 마리아 위치
    mapRects.push_back({ 50, 70, 32, 32 }); // 비르투스 위치
    mapRects.push_back({ 90, 70, 32, 32 }); // 밤비노 위치
    mapRects.push_back({ 90, 50, 32, 32 }); // 다솔 위치
    mapRects.push_back({ 126, 50, 32, 32 }); // 학생회관 위치
    mapRects.push_back({ 126, 28, 32, 32 }); // 미카엘 위치
    mapRects.push_back({ 126, 5, 32, 32 }); // 최종장 위치

    playerRect.x = mapRects[currentMapIndex].x;
    playerRect.y = mapRects[currentMapIndex].y;
}

Minimap::~Minimap() {
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyTexture(playerTexture);
}

void Minimap::Render(int playerX, int playerY) {
    // 미니맵 렌더링
    SDL_Rect mapRect = { 0, 0, 160, 160 }; // 미니맵 크기 설정
    SDL_RenderCopy(renderer, mapTexture, NULL, &mapRect);

    // 플레이어 아이콘 렌더링
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
}

void Minimap::UpdatePlayerPosition(int mapIndex) {
    if (mapIndex < 0 || mapIndex >= mapRects.size()) {
        std::cerr << "Invalid map index" << std::endl;
        return;
    }
    currentMapIndex = mapIndex;
    playerRect.x = mapRects[mapIndex].x;
    playerRect.y = mapRects[mapIndex].y;
}
