#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

class Item
{
public:
    float x, y, w, h;
    SDL_Texture *texture;
    SDL_Rect itemRect;

    Item(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h);
    void render(SDL_Renderer *renderer);
    SDL_Rect getRect();
};

#endif // ITEM_H