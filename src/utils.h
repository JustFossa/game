#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

SDL_Surface *loadSurface(std::string path, SDL_Window *window);
SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer);
SDL_Texture *renderText(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Rect *textRect);

#endif // UTILS_H
