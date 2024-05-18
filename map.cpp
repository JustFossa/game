#include "map.h"
#include "utils.h"  // Utility functions like loadTexture

Map::Map(SDL_Renderer* renderer, std::string path, float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->texture = loadTexture(path, renderer);
}

void Map::render(SDL_Renderer* renderer) {
    SDL_Rect mapRect = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h) };
    SDL_RenderCopy(renderer, texture, NULL, &mapRect);
}