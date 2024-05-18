#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <string>

SDL_Surface* loadSurface(std::string path, SDL_Window* window);
SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

#endif // UTILS_H
