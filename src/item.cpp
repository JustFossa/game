#include "item.h"
#include "utils.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

Item::Item(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->texture = loadTexture(path, renderer);
    this->itemRect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)};
}

void Item::render(SDL_Renderer *renderer)
{
    SDL_Rect itemRect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)};
    SDL_RenderCopy(renderer, texture, NULL, &itemRect);
}

SDL_Rect Item::getRect()
{
    return itemRect;
}