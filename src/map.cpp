#include "map.h"
#include "utils.h" // Utility functions like loadTexture

Map::Map(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h, std::vector<Item *> items)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->texture = loadTexture(path, renderer);
    this->collisionRects = {
        {0, 0, 100, 100},
        {200, 200, 100, 100},
        {400, 400, 100, 100},
    };
    this->items = items;
}

void Map::render(SDL_Renderer *renderer)
{
    SDL_Rect mapRect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRects(renderer, collisionRects.data(), collisionRects.size());
    for (auto &item : items)
    {
        item->render(renderer);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

std::vector<SDL_Rect> Map::getCollisionRects()
{
    return collisionRects;
}

std::vector<Item *> Map::getItems()
{
    return items;
}