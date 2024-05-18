#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "utils.h"
#include "map.h"

class Player
{
public:
    SDL_Rect playerRect;
    SDL_Texture *texture;
    float speed;

    Player(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h, float speed);
    void render(SDL_Renderer *renderer);
    void move(Map *map);
    void gravity(Map *map);
    void jump(Map *map);
};

#endif // PLAYER_H