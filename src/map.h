#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "item.h"

class Map
{
public:
    float x, y, w, h;
    SDL_Texture *texture;
    std::vector<SDL_Rect> collisionRects;
    std::vector<Item *> items;

    Map(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h, std::vector<Item *> items);
    void render(SDL_Renderer *renderer);
    std::vector<SDL_Rect> getCollisionRects();
    std::vector<Item *> getItems();
};

#endif // MAP_H