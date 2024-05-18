#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Map {
public:
    float x, y, w, h;
    SDL_Texture* texture;

    Map(SDL_Renderer* renderer, std::string path, float x, float y, float w, float h);
    void render(SDL_Renderer* renderer);
};

#endif // MAP_H