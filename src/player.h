#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "map.h"
#include "item.h"
#include <vector>
#include "healthbar.h"

class Player
{
public:
    SDL_Rect playerRect;
    std::vector<Item *> playerItems;
    HealthBar *healthBar;

    Player(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h, float speed, HealthBar *healthBar);

    void render(SDL_Renderer *renderer);
    void move(Map *map);
    void addItem(Item *item);
    std::vector<Item *> getItems();

private:
    SDL_Texture *texture;

    float speed;

    void checkCollisionWithMap(Map *map, SDL_Rect &potentialRect);

    void checkCollision(SDL_Rect &obstacle, SDL_Rect &potentialRect);

    void checkCollisionWithItems(Map *map);
};

#endif // PLAYER_H
