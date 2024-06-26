#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "map.h"
#include "utils.h"
#include "player.h"
#include "item.h"
#include "animation.h"
#include "json.h"
#include "healthbar.h"
#include <nlohmann/json.hpp>
#include "hud.h"
#include "inventory.h"

void init();

HealthBar *healthBar;
Inventory *inventory;
HUD *hud;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const float SPEED = 5;

const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;

const int FRAME_RATE = 60;

const float DELAY = 1000 / FRAME_RATE;

Uint32 frameTime = 1000 / FRAME_RATE;

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

struct particle
{
    std::string texture;
    int x, y, frameWidth, frameHeight, frameCount, frameRate, perRow;
};

std::vector<Animation *> animations;
std::vector<Item *> items;
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
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
                if (TTF_Init() == -1)
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
                    while (!quit)
                    {
                        Uint32 frameStart = SDL_GetTicks64();
                        std::string statsString = "X: " + std::to_string(player->playerRect.x) + " Y: " + std::to_string(player->playerRect.y) + " FPS: " + std::to_string(1000 / frameTime);
                        SDL_RenderClear(renderer);
                        TTF_Font *font = TTF_OpenFont("assets/fonts/OpenSans.ttf", 24);
                        SDL_Texture *stats = renderText(renderer, statsString, "assets/fonts/OpenSans.ttf", {255, 255, 255, 255}, 24, &statsRect);
                        SDL_RenderCopy(renderer, stats, NULL, &statsRect);
                        SDL_DestroyTexture(stats);
                        TTF_CloseFont(font);

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

                        hud->render(renderer);
                        hud->getInventory()->update();
                        hud->getInventory()->renderItems(renderer);

                        for (auto animation : animations)
                        {
                            animation->update();
                            animation->render(renderer);
                        }

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
    nlohmann::json particles = loadJson("assets/particles.json");
    for (auto &particle : particles)
    {
        animations.push_back(new Animation(renderer, particle["texture"], particle["x"], particle["y"], particle["frameWidth"], particle["frameHeight"], particle["frameCount"], particle["frameRate"], particle["perRow"]));
    }
    map = new Map(renderer, "assets/bg.jpg", viewport.x, viewport.y, viewport.w, viewport.h, items);
    map->render(renderer);
    healthBar = new HealthBar(renderer, "assets/healthbar.png", 100, 100, SCREEN_WIDTH - 240, -25, 48, 16, 6);
    inventory = new Inventory(renderer, "assets/inventory.png", SCREEN_WIDTH - 3 * 32 * 3, SCREEN_HEIGHT - 3 * 32, 32, 32, 4);
    inventory->initSlots(3);
    hud = new HUD(renderer, healthBar, inventory);
    player = new Player(renderer, "assets/player.png", playerRect.x, playerRect.y, playerRect.w, playerRect.h, SPEED, hud);
    player->render(renderer);
}