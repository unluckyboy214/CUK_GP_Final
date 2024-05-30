#include "Minimap.h"
#include <SDL_image.h>
#include <iostream>

Minimap::Minimap(SDL_Renderer* renderer) : renderer(renderer), currentMapIndex(0) {
    // �� �ؽ�ó �ε�
    SDL_Surface* mapSurface = IMG_Load("../../Resource/Map/minimap.png");
    mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    SDL_FreeSurface(mapSurface);

    // �÷��̾� �ؽ�ó �ε�
    SDL_Surface* playerSurface = IMG_Load("../../Resource/Character/player_icon.png");
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    SDL_FreeSurface(playerSurface);

    // �÷��̾� Rect �ʱ�ȭ
    playerRect = { 0, 0, 16, 16 }; // �÷��̾� ������ ũ�� ����

    // �̴ϸ��� �� ��ġ�� �����ϴ� Rect �ʱ�ȭ
    mapRects.push_back({ 10, 140, 32, 32 }); // ���� ��ġ
    mapRects.push_back({ 10, 115, 32, 32 }); // ���ȯ ��ġ
    mapRects.push_back({ 10, 95, 32, 32 }); // ���� ��ġ
    mapRects.push_back({ 50, 95, 32, 32 }); // ���ݽ�1 ��ġ
    mapRects.push_back({ 90, 95, 32, 32 }); // ���ݽ�2 ��ġ
    mapRects.push_back({ 130, 95, 32, 32 }); // ���ݽ�3 ��ġ
    mapRects.push_back({ 130, 115, 32, 32 }); // ������ ��ġ
    mapRects.push_back({ 50, 70, 32, 32 }); // ������ ��ġ
    mapRects.push_back({ 90, 70, 32, 32 }); // ���� ��ġ
    mapRects.push_back({ 90, 50, 32, 32 }); // �ټ� ��ġ
    mapRects.push_back({ 126, 50, 32, 32 }); // �л�ȸ�� ��ġ
    mapRects.push_back({ 126, 28, 32, 32 }); // ��ī�� ��ġ
    mapRects.push_back({ 126, 5, 32, 32 }); // ������ ��ġ

    playerRect.x = mapRects[currentMapIndex].x;
    playerRect.y = mapRects[currentMapIndex].y;
}

Minimap::~Minimap() {
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyTexture(playerTexture);
}

void Minimap::Render(int playerX, int playerY) {
    // �̴ϸ� ������
    SDL_Rect mapRect = { 0, 0, 160, 160 }; // �̴ϸ� ũ�� ����
    SDL_RenderCopy(renderer, mapTexture, NULL, &mapRect);

    // �÷��̾� ������ ������
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
