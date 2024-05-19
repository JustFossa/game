#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_timer.h>
#include "map.h"
#include "utils.h"
#include "player.h"
#include "item.h"

void init();

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const float SPEED = 5;

const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;

const float DELAY = 1000 / 60;

Uint32 frameTime = 1000 / 60;

SDL_Rect playerRect = {
    SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2,
    SCREEN_HEIGHT - PLAYER_HEIGHT,
    PLAYER_WIDTH,
    PLAYER_HEIGHT};

SDL_Rect viewport = {
    0,
    0,
    SCREEN_WIDTH,
    SCREEN_HEIGHT};

SDL_Rect statsRect = {
    10,
    10,
    0,
    0};

std::vector<Item *> items;
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *currentSurface = NULL;
SDL_Renderer *renderer = NULL;
Map *map = NULL;
Player *player = NULL;

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! Error: %s\n", SDL_GetError());
        return -1;
    }
    else
    {
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window creation failed! Error: %s\n", SDL_GetError());
            return -1;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! Error: %s\n", SDL_GetError());
                return -1;
            }
            else
            {
                int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP;

                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_Image could not initialize! Error: %s\n", IMG_GetError());
                    return -1;
                }
                if (!TTF_Init() < 0)
                {
                    printf("SDL_ttf could not initialize! Error: %s\n", TTF_GetError());
                    return -1;
                }
                else
                {
                    screenSurface = SDL_GetWindowSurface(window);
                    SDL_Event e;
                    bool quit = false;

                    init();
                    while (quit == false)
                    {
                        Uint32 frameStart = SDL_GetTicks64();
                        std::string statsString = "X: " + std::to_string(player->playerRect.x) + " Y: " + std::to_string(player->playerRect.y) + " FPS: " + std::to_string(1000 / frameTime);
                        SDL_RenderClear(renderer);
                        TTF_Font *font = TTF_OpenFont("assets/fonts/OpenSans.ttf", 24);
                        SDL_Texture *stats = renderText(renderer, statsString, "assets/fonts/OpenSans.ttf", {255, 255, 255, 255}, 24, &statsRect);
                        SDL_RenderCopy(renderer, stats, NULL, &statsRect);
                        while (SDL_PollEvent(&e) != 0)
                        {
                            if (e.type == SDL_QUIT)
                            {
                                quit = true;
                            }
                        }
                        player->move(map);
                        player->render(renderer);
                        map->render(renderer);
                        SDL_RenderPresent(renderer);
                        frameTime = SDL_GetTicks64() - frameStart;
                        if (frameTime < DELAY)
                        {
                            SDL_Delay(DELAY - frameTime);
                        }
                    }
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void init()
{
    SDL_RenderClear(renderer);
    items.push_back(new Item(renderer, "assets/item.png", 100, 100, 50, 50));
    map = new Map(renderer, "assets/bg.png", viewport.x, viewport.y, viewport.w, viewport.h, items);
    map->render(renderer);
    player = new Player(renderer, "assets/player.png", playerRect.x, playerRect.y, playerRect.w, playerRect.h, SPEED);
    player->render(renderer);
}
