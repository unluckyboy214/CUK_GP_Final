#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PLAYER_SIZE = 10;
const int PLAYER_SPEED = 5;  // 플레이어 속도
const int FRAME_RATE = 60;   // 초당 프레임 수

bool init();
bool loadMedia();
void close();
void handleInput(bool& quit, bool* keys);

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gBackgroundTexture = nullptr;

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_JPG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    SDL_Surface* loadedSurface = IMG_Load("../../Resource/bg1.jpg");
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
        success = false;
    }
    else {
        gBackgroundTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (gBackgroundTexture == nullptr) {
            std::cerr << "Unable to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        SDL_FreeSurface(loadedSurface);
    }

    return success;
}

void close() {
    SDL_DestroyTexture(gBackgroundTexture);
    gBackgroundTexture = nullptr;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
}

void handleInput(bool& quit, bool* keys) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_w:
                keys[0] = true;
                break;
            case SDLK_a:
                keys[1] = true;
                break;
            case SDLK_s:
                keys[2] = true;
                break;
            case SDLK_d:
                keys[3] = true;
                break;
            }
        }
        else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
            case SDLK_w:
                keys[0] = false;
                break;
            case SDLK_a:
                keys[1] = false;
                break;
            case SDLK_s:
                keys[2] = false;
                break;
            case SDLK_d:
                keys[3] = false;
                break;
            }
        }
    }
}

void updatePlayer(SDL_Rect& player, bool* keys) {
    if (keys[0]) player.y -= PLAYER_SPEED;  // W
    if (keys[1]) player.x -= PLAYER_SPEED;  // A
    if (keys[2]) player.y += PLAYER_SPEED;  // S
    if (keys[3]) player.x += PLAYER_SPEED;  // D

    // 플레이어가 화면 경계를 벗어나지 않도록 조정
    if (player.x < 0) player.x = 0;
    if (player.x > SCREEN_WIDTH - PLAYER_SIZE) player.x = SCREEN_WIDTH - PLAYER_SIZE;
    if (player.y < 0) player.y = 0;
    if (player.y > SCREEN_HEIGHT - PLAYER_SIZE) player.y = SCREEN_HEIGHT - PLAYER_SIZE;
}

int main(int argc, char* args[]) {
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
    }
    else {
        if (!loadMedia()) {
            std::cerr << "Failed to load media!" << std::endl;
        }
        else {
            bool quit = false;
            SDL_Rect player = { SCREEN_WIDTH / 2 - PLAYER_SIZE / 2, SCREEN_HEIGHT / 2 - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE };
            bool keys[4] = { false, false, false, false };

            Uint32 frameDelay = 1000 / FRAME_RATE;
            Uint32 frameStart;
            int frameTime;

            while (!quit) {
                frameStart = SDL_GetTicks();

                handleInput(quit, keys);
                updatePlayer(player, keys);

                SDL_RenderClear(gRenderer);
                SDL_RenderCopy(gRenderer, gBackgroundTexture, nullptr, nullptr);
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(gRenderer, &player);
                SDL_RenderPresent(gRenderer);

                frameTime = SDL_GetTicks() - frameStart;

                if (frameDelay > frameTime) {
                    SDL_Delay(frameDelay - frameTime);
                }
            }
        }
    }

    close();

    return 0;
}
